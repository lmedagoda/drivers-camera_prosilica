/* 
 * File:   CamGigEProsilicaLookUp.h
 * Author: aduda
 *
 * Created on February 24, 2010, 11:32 AM
 */

#ifndef _CAMGIGEPROSILICALOOKUP_H
#define	_CAMGIGEPROSILICALOOKUP_H

#include "camera_interface/CamTypes.h"
#include <map>

namespace camera
{
    
    inline static void attribToStr(enum_attrib::CamAttrib attrib,
                            std::string &string1,
                            std::string &string2)
    {
        switch(attrib)
        {
            case enum_attrib::FrameStartTriggerModeToFreerun:
                string1 = "FrameStartTriggerMode";
                string2 = "Freerun";
                break;
            case enum_attrib::FrameStartTriggerModeToSyncIn1:
                string1 = "FrameStartTriggerMode";
                string2 = "SyncIn1";
                break;
            case enum_attrib::FrameStartTriggerModeToSyncIn2:
                string1 = "FrameStartTriggerMode";
                string2 = "SyncIn2";
                break;
            case enum_attrib::FrameStartTriggerModeToSyncIn3:
                string1 = "FrameStartTriggerMode";
                string2 = "SyncIn3";
                break;
            case enum_attrib::FrameStartTriggerModeToSyncIn4:
                string1 = "FrameStartTriggerMode";
                string2 = "SyncIn4";
                break;
            case enum_attrib::FrameStartTriggerModeToFixedRate:
                string1 = "FrameStartTriggerMode";
                string2 = "FixedRate";
                break;
            case enum_attrib::FrameStartTriggerModeToSoftware:
                string1 = "FrameStartTriggerMode";
                string2 = "Software";
                break;
            case enum_attrib::ExposureModeToManual:
                string1 = "ExposureMode";
                string2 = "Manual";
                break;
            case enum_attrib::ExposureModeToAuto:
                string1 = "ExposureMode";
                string2 = "Auto";
                break;
            case enum_attrib::ExposureModeToAutoOnce:
                string1 = "ExposureMode";
                string2 = "AutoOnce";
                break;
	    case enum_attrib::GainModeToManual:
                string1 = "GainMode";
                string2 = "Manual";
                break;
            case enum_attrib::GainModeToAuto:
                string1 = "GainMode";
                string2 = "Auto";
                break;
		
            default:
               throw std::runtime_error("Attribute is not supported by the "
                       "camera. Call isAttribAvail first!");
        }
    }

    inline static void attribToStr(str_attrib::CamAttrib attrib,std::string &string)
    {
        switch(attrib)
        {
            case str_attrib::DeviceEthAddress:
                string = "DeviceEthAddress";
                break;
            case str_attrib::DeviceIPAddress:
                string = "DeviceIPAddress";
                break;
            case str_attrib::HostIPAddress:
                string = "HostIPAddress";
                break;
            case str_attrib::MulticastIPAddress:
                string = "MulticastIPAddress";
                break;
            case str_attrib::CameraName:
                string = "CameraName";
                break;
            case str_attrib::ModelName:
                string = "ModelName";
                break;
            case str_attrib::SerialNumber:
                string = "SerialNumber";
                break;
            case str_attrib::PartRevision:
                string = "PartRevision";
                break;
            case str_attrib::StatFilterVersion:
                string = "StatFilterVersion";
                break;
            default:
               throw std::runtime_error("Attribute is not supported by the "
                       "camera. Call isAttribAvail first!");
        }
    }

    inline static void attribToStr(double_attrib::CamAttrib attrib,std::string &string)
    {
        switch(attrib)
        {
            case double_attrib::FrameRate:
                string = "FrameRate";
                break;
            case double_attrib::StatFrameRate:
                string = "StatFrameRate";
                break;
            default:
               throw std::runtime_error("Attribute is not supported by the "
                       "camera. Call isAttribAvail first!");
        }
    }
    
    inline static void attribToStr(int_attrib::CamAttrib attrib,std::string &string)
    {
        switch(attrib)
        {
            case int_attrib::BinningX:
                string = "BinningX";
                break;
            case int_attrib::BinningY:
                string = "BinningY";
                break;
            case int_attrib::RegionX:
                string = "RegionX";
                break;
            case int_attrib::RegionY:
                string = "RegionY";
                break;
            case int_attrib::TotalBytesPerFrame:
                string = "TotalBytesPerFrame";
                break;
            case int_attrib::AcquisitionFrameCount:
                string = "AcquisitionFrameCount";
                break;
            case int_attrib::RecorderPreEventCount:
                string = "RecorderPreEventCount";
                break;
            case int_attrib::FrameStartTriggerDelay:
                string = "FrameStartTriggerDelay";
                break;
            case int_attrib::ExposureValue:
                string = "ExposureValue";
                break;
            case int_attrib::ExposureAutoMax:
                string = "ExposureAutoMax";
                break;
            case int_attrib::ExposureAutoMin:
                string = "ExposureAutoMin";
                break;
            case int_attrib::ExposureAutoOutliers:
                string = "ExposureAutoOutliers";
                break;
            case int_attrib::ExposureAutoRate:
                string = "ExposureAutoRate";
                break;
            case int_attrib::ExposureAutoTarget:
                string = "ExposureAutoTarget";
                break;
            case int_attrib::ExposureAutoAdjustTol:
                string = "ExposureAutoAdjustTol";
                break;
            case int_attrib::GainValue:
                string = "GainValue";
                break;
            case int_attrib::GainAutoAdjustDelay:
                string = "GainAutoAdjustDelay";
                break;
            case int_attrib::GainAutoAdjustTol:
                string = "GainAutoAdjustTol";
                break;
            case int_attrib::GainAutoMax:
                string = "GainAutoMax";
                break;
            case int_attrib::GainAutoMin:
                string = "GainAutoMin";
                break;
            case int_attrib::GainAutoOutliers:
                string = "GainAutoOutliers";
                break;
            case int_attrib::GainAutoRate:
                string = "GainAutoRate";
                break;
            case int_attrib::GainAutoTarget:
                string = "ExposureAutoAdjustTol";
                break;
            case int_attrib::WhitebalValueRed:
                string = "WhitebalValueRed";
                break;
            case int_attrib::WhitebalValueBlue:
                string = "WhitebalValueBlue";
                break;
            case int_attrib::WhitebalAutoAdjustDelay:
                string = "WhitebalAutoAdjustDelay";
                break;
            case int_attrib::WhitebalAutoAdjustTol:
                string = "WhitebalAutoAdjustTol";
                break;
            case int_attrib::WhitebalAutoAlg:
                string = "WhitebalAutoAlg";
                break;
            case int_attrib::WhitebalAutoRate:
                string = "WhitebalAutoRate";
                break;
            case int_attrib::OffsetValue:
                string = "OffsetValue";
                break;
            case int_attrib::DSPSubregionLeft:
                string = "DSPSubregionLeft";
                break;
            case int_attrib::DSPSubregionTop:
                string = "DSPSubregionTop";
                break;
            case int_attrib::DSPSubregionRight:
                string = "DSPSubregionRight";
                break;
            case int_attrib::DSPSubregionBottom:
                string = "DSPSubregionBottom";
                break;
            case int_attrib::IrisAutoTarget:
                string = "IrisAutoTarget";
                break;
            case int_attrib::IrisVideoLevelMin:
                string = "IrisVideoLevelMin";
                break;
            case int_attrib::IrisVideoLevelMax:
                string = "IrisVideoLevelMax";
                break;
            case int_attrib::IrisVideoLevel:
                string = "IrisVideoLevel";
                break;
            case int_attrib::SyncInLevels:
                string = "SyncInLevels";
                break;
            case int_attrib::SyncOutGpoLevels:
                string = "SyncOutGpoLevels";
                break;
            case int_attrib::Strobe1Delay:
                string = "Strobe1Delay";
                break;
            case int_attrib::Strobe1Duration:
                string = "Strobe1Duration";
                break;
            case int_attrib::PacketSize:
                string = "PacketSize";
                break;
            case int_attrib::StreamBytesPerSecond:
                string = "StreamBytesPerSecond";
                break;
            case int_attrib::GvcpRetries:
                string = "GvcpRetries";
                break;
            case int_attrib::HeartbeatTimeout:
                string = "HeartbeatTimeout";
                break;
            case int_attrib::HeartbeatInterval:
                string = "HeartbeatInterval";
                break;
            case int_attrib::StreamHoldCapacity:
                string = "StreamHoldCapacity";
                break;
            case int_attrib::UniqueId:
                string = "UniqueId";
                break;
            case int_attrib::PartNumber:
                string = "PartNumber";
                break;
            case int_attrib::PartVersion:
                string = "PartVersion";
                break;
            case int_attrib::FirmwareVerMajor:
                string = "FirmwareVerMajor";
                break;
            case int_attrib::FirmwareVerMinor:
                string = "FirmwareVerMinor";
                break;
            case int_attrib::FirmwareVerBuild:
                string = "FirmwareVerBuild";
                break;
            case int_attrib::SensorBits:
                string = "SensorBits";
                break;
            case int_attrib::SensorWidth:
                string = "SensorWidth";
                break;
            case int_attrib::SensorHeight:
                string = "SensorHeight";
                break;
            case int_attrib::TimeStampFrequency:
                string = "TimeStampFrequency";
                break;
            case int_attrib::StatFramesCompleted:
                string = "StatFramesCompleted";
                break;
            case int_attrib::StatFramesDropped:
                string = "StatFramesDropped";
                break;
            case int_attrib::StatPacketsErroneous:
                string = "StatPacketsErroneous";
                break;
            case int_attrib::StatPacketsMissed:
                string = "StatPacketsMissed";
                break;
            case int_attrib::StatPacketsReceived:
                string = "StatPacketsReceived";
                break;
            case int_attrib::StatPacketsRequested:
                string = "StatPacketsRequested";
                break;
            case int_attrib::StatPacketsResent:
                string = "StatPacketsResent";
                break;
            default:
               throw std::runtime_error("Attribute is not supported by the "
                       "camera. Call isAttribAvail first!");
        }
    }

    inline static void convertStrToPixelFormat(const std::string &str,
                                               frame_mode_t &mode,
                                               uint8_t &depth)
    {
        if(str == "Mono8")
        {
            mode = MODE_GRAYSCALE;
            depth = 1;
        }
        else if(str == "Mono16")
        {
            mode = MODE_GRAYSCALE;
            depth = 2;
        }
        else if(str == "Rgb24")
        {
            mode = MODE_RGB;
            depth = 3;
        }
        else if(str == "Rgb48")
        {
            mode = MODE_RGB;
            depth = 6;
        }
        else
        {
            throw std::runtime_error("Can not convert string to PixelFormat! "
                    "Add the actual camera frame format to the CamInterface");
        }

    }

    inline static std::string convertPixelFormatToStr(const frame_mode_t mode,
                                                            const uint8_t depth)
    {
        switch (mode)
        {
            case MODE_GRAYSCALE:
                switch(depth)
                {
                    case 1:
                       return "Mono8";
                        break;
                    case 2:
                        return "Mono16";
                        break;
                    default:
                        throw std::runtime_error("Choosen color depth value is "
                                                "not supported by the camera!");
                }
                break;
             case MODE_RGB:
                switch(depth)
                {
                    case 3:
                        return "Rgb24";
                        break;
                    case 6:
                        return "Rgb48";
                        break;
                    default:
                        throw std::runtime_error("Choosen color depth value is "
                                                "not supported by the camera!");
                }
                break;
            default:
                throw std::runtime_error("Frame mode is not supported by"
                                         " the camera!");
        }
        return "";
    }
}

#endif	/* _CAMGIGEPROSILICALOOKUP_H */

