/* 
 * File:   CameraProsilica.h
 * Author: Alexander Duda
 *
 * Created on February 9, 2010, 8:39 AM
 */

#ifndef _CAMGIGEPROSILICA_H
#define	_CAMGIGEPROSILICA_H

#define REG_SIO_INQUIRY			0x16000
#define REG_SIO_MODE_INQUIRY		0x16100
#define REG_SIO_MODE			0x16104
#define REG_SIO_TX_INQUIRY		0x16120
#define REG_SIO_TX_STATUS		0x16124
#define REG_SIO_TX_CONTROL		0x16128
#define REG_SIO_TX_LENGTH		0x1612C
#define REG_SIO_RX_INQUIRY		0x16140
#define REG_SIO_RX_STATUS		0x16144
#define REG_SIO_RX_CONTROL		0x16148
#define REG_SIO_RX_LENGTH		0x1614C
#define REG_SIO_TX_BUFFER		0x16400
#define REG_SIO_RX_BUFFER		0x16800


#include <camera_interface/CamInterface.h>
#include "arch.h"
#include "PvApi.h"
#include "PvRegIo.h"
#include <list>

namespace camera
{
    struct ProFrame
    {
    private:
        std::vector<uint8_t> data;
    public:
        tPvFrame frame;
	base::Time timestamp_received; 
	
        ProFrame( int frame_size_in_byte)
        {
            resize(frame_size_in_byte);
	    
        }
        
        inline void swap(base::samples::frame::Frame &other)
        {
            if(data.size() != other.image.size())
                 throw std::runtime_error("Frame size mismatch. "
                                          " Can not swap data.");
            other.image.swap(data);
            frame.ImageBuffer = &data[0];
	    
	    other.attributes.clear();
	    if(frame.Status == ePvErrSuccess) 
	      other.setStatus(base::samples::frame::STATUS_VALID);
	    else
	      other.setStatus(base::samples::frame::STATUS_INVALID);
	
	    //Rolling frame counter. For GigE Vision cameras, this
	    //corresponds to the block number, which rolls from 1 to 0xFFFF
	    other.setAttribute<uint16_t>("FrameCount",frame.FrameCount);
	    other.time = timestamp_received;
	    other.received_time = timestamp_received;
	    
	    switch(frame.Format)
	    {
	      //check bayer pattern 
	      case ePvFmtBayer8:
	      case ePvFmtBayer16:
		switch (frame.BayerPattern)
		{
		  case ePvBayerRGGB:
		    if(other.getFrameMode() != base::samples::frame::MODE_BAYER_RGGB)
		    {
		      if(other.getFrameMode() == base::samples::frame::MODE_BAYER)
			other.frame_mode = base::samples::frame::MODE_BAYER_RGGB;
		      else
			throw std::runtime_error("Bayer Pattern is MODE_BAYER_RGGB but frame has a "
						  "different format. Use MODE_BAYER if you want to use auto discover.");
		    }
		    break;
	    
		  case ePvBayerGBRG:
		    if(other.getFrameMode() != base::samples::frame::MODE_BAYER_GBRG)
		    {
		      if(other.getFrameMode() == base::samples::frame::MODE_BAYER)
			other.frame_mode = base::samples::frame::MODE_BAYER_GBRG;
		      else
			throw std::runtime_error("Bayer Pattern is MODE_BAYER_GBRG but frame has a "
						  "different format. Use MODE_BAYER if you want to use auto discover.");
		    }
		    break;
	    
		  case ePvBayerGRBG:
		    if(other.getFrameMode() != base::samples::frame::MODE_BAYER_GRBG)
		    {
		      if(other.getFrameMode() == base::samples::frame::MODE_BAYER)
			other.frame_mode = base::samples::frame::MODE_BAYER_GRBG;
		      else
			throw std::runtime_error("Bayer Pattern is MODE_BAYER_GRBG but frame has a "
						  "different format. Use MODE_BAYER if you want to use auto discover.");
		    }
		    break;
		      
		  case ePvBayerBGGR:
		    if(other.getFrameMode() != base::samples::frame::MODE_BAYER_BGGR)
		    {
		      if(other.getFrameMode() == base::samples::frame::MODE_BAYER)
			other.frame_mode = base::samples::frame::MODE_BAYER_BGGR;
		      else
			throw std::runtime_error("Bayer Pattern is MODE_BAYER_BGGR but frame has a "
						  "different format. Use MODE_BAYER if you want to use auto discover.");
		    }
		    break;
	    
		  default:	//unknown bayer pattern
		    throw std::runtime_error("Unknown Bayer Patter");
		}
		break;
	    
		case ePvFmtMono8:
		case ePvFmtMono16:
		  if(other.getFrameMode() != base::samples::frame::MODE_GRAYSCALE)
		      throw std::runtime_error("Color format is MONO but frame has a different format.");
		break; 
		
		case ePvFmtRgb24:
		case ePvFmtRgb48:
		  if(other.getFrameMode() != base::samples::frame::MODE_RGB)
		      throw std::runtime_error("Color format is RGB but frame has a different format.");
		break; 
		
		default:
		{
		  if(other.getFrameMode() != base::samples::frame::MODE_UNDEFINED)
		    throw std::runtime_error("Unknown frame color format!!!");
		}
	    }
        }

        inline void resize( int frame_size_in_byte)
        {
            data.resize(frame_size_in_byte);
            frame.ImageBuffer = &data[0];
            frame.ImageBufferSize = frame_size_in_byte;
            frame.AncillaryBuffer     = NULL;
	    frame.Context[0] = &timestamp_received;
	    // frame.Context[1] is used for user callback

           //using AncillaryBufferSize to indicate if frame is done
           //0 --> frame is done
           //1 --> frame is not done
           //faster than PvCaptureWaitForFrameDone
           frame.AncillaryBufferSize = 0;
        } 
    };

    class CamGigEProsilica : public CamInterface
    {
    private:
        tPvHandle camera_handle_;
        CamInfo cam_info_;
        static int instance_count_;
        std::list<ProFrame*> frame_queue_;
        int frame_size_in_byte_;
        AccessMode access_mode_;
	void (*pcallback_function_)(const void* p);
	void *pass_through_pointer_;
	double timestamp_factor;
	uint64_t timestamp_offset_camera_system; 	//in micro seconds
	
	uint32_t max_package_size_t; //max package size of the ethernet packages (mtu) in byte (defaul is 16110)						    

    public:
        CamGigEProsilica(uint32_t max_package_size = 16110);
        ~CamGigEProsilica();

    public:
        int listCameras(std::vector<CamInfo>&cam_infos)const;
        bool open(const CamInfo &cam,const AccessMode mode);
        bool open(const std::string &ip,const AccessMode mode);
        bool isOpen()const;
        bool close();
	const CamInfo *getCameraInfo()const;

        bool grab(const GrabMode mode, const int buffer_len);
        bool retrieveFrame(base::samples::frame::Frame &frame,const int timeout);
        bool setFrameSettings(const base::samples::frame::frame_size_t size,
                              const base::samples::frame::frame_mode_t mode,
                              const  uint8_t color_depth,
                              const bool resize_frames);
        bool isFrameAvailable();
        int skipFrames();

        bool setAttrib(const int_attrib::CamAttrib attrib,const int value);
        bool setAttrib(const double_attrib::CamAttrib attrib,const double value);
        bool setAttrib(const enum_attrib::CamAttrib attrib);
        bool setAttrib(const str_attrib::CamAttrib attrib,const std::string &string);

        bool isAttribAvail(const int_attrib::CamAttrib attrib);
        bool isAttribAvail(const str_attrib::CamAttrib attrib);
        bool isAttribAvail(const double_attrib::CamAttrib attrib);
        bool isAttribAvail(const enum_attrib::CamAttrib attrib);

        int getAttrib(const int_attrib::CamAttrib attrib);
        double getAttrib(const double_attrib::CamAttrib attrib);
        std::string getAttrib(const str_attrib::CamAttrib attrib);
        bool isAttribSet(const enum_attrib::CamAttrib attrib);

        bool getFrameSettings(base::samples::frame::frame_size_t &size,
			      base::samples::frame::frame_mode_t &mode,
			      uint8_t &color_depth);

        bool triggerFrame();
	
	bool setCallbackFcn(void (*pcallback_function)(const void* p),void *p);
	void callUserCallbackFcn()const;
        void synchronizeWithSystemTime(uint32_t time_interval);
        void saveConfiguration(uint8_t index);
        void loadConfiguration(uint8_t index);
	
	void getRange(const double_attrib::CamAttrib attrib,double &dmin,double &dmax);
	void getRange(const int_attrib::CamAttrib attrib,int &imin,int &imax);
	
	// Various serial-io operations (return true if successful)
	bool F_DisplayInfo(tPvHandle camera);
	bool F_SetupSio(tPvHandle camera);
	bool F_ReadData(tPvHandle camera, unsigned char* buffer, unsigned long bufferLength, unsigned long* pReceiveLength);
	bool F_WriteData(tPvHandle camera, const unsigned char* buffer, unsigned long length);
	// Read a byte array from the camera.
	bool F_ReadMem(tPvHandle camera, unsigned long address, unsigned char* buffer, unsigned long length);
	// Write a byte array to the camera. 
	bool F_WriteMem(tPvHandle camera, unsigned long address, const unsigned char* buffer, unsigned long length);
	
    private:
        //helpers
        void copy_tPvCameraInfo_To_tCamInfo
                        (const tPvCameraInfo& source, CamInfo& dest) const;
        bool fillCameraIpSettings(CamInfo& cam)const;
        bool prepareQueueForGrabbing(const int queue_len);
        inline bool isFrameQueued(const ProFrame* frame);
        inline bool queueFrame(ProFrame* frame);
        static void callBack(tPvFrame * frame);
	static void callBack2(tPvFrame * frame);
	
	void checkCameraStatus()const;
	void setConfigFileIndex(uint8_t index);
    };
}


#endif	/* _CAMGIGEPROSILICA_H */

