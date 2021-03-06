#pragma once

#include "Emu/Io/PadHandler.h"
#include <Windows.h>
#include <mmsystem.h>
#include "Utilities/Config.h"

class mm_joystick_handler final : public PadHandlerBase
{
	// Unique names for the config files and our pad settings dialog
	const std::unordered_map<u64, std::string> button_list =
	{
		{ JOY_BUTTON1 , "Button 1"  },
		{ JOY_BUTTON2 , "Button 2"  },
		{ JOY_BUTTON3 , "Button 3"  },
		{ JOY_BUTTON4 , "Button 4"  },
		{ JOY_BUTTON5 , "Button 5"  },
		{ JOY_BUTTON6 , "Button 6"  },
		{ JOY_BUTTON7 , "Button 7"  },
		{ JOY_BUTTON8 , "Button 8"  },
		{ JOY_BUTTON9 , "Button 9"  },
		{ JOY_BUTTON10, "Button 10" },
		{ JOY_BUTTON11, "Button 11" },
		{ JOY_BUTTON12, "Button 12" },
		{ JOY_BUTTON13, "Button 13" },
		{ JOY_BUTTON14, "Button 14" },
		{ JOY_BUTTON15, "Button 15" },
		{ JOY_BUTTON16, "Button 16" },
		{ JOY_BUTTON17, "Button 17" },
		{ JOY_BUTTON18, "Button 18" },
		{ JOY_BUTTON19, "Button 19" },
		{ JOY_BUTTON20, "Button 20" },
		{ JOY_BUTTON21, "Button 21" },
		{ JOY_BUTTON22, "Button 22" },
		{ JOY_BUTTON23, "Button 23" },
		{ JOY_BUTTON24, "Button 24" },
		{ JOY_BUTTON25, "Button 25" },
		{ JOY_BUTTON26, "Button 26" },
		{ JOY_BUTTON27, "Button 27" },
		{ JOY_BUTTON28, "Button 28" },
		{ JOY_BUTTON29, "Button 29" },
		{ JOY_BUTTON30, "Button 30" },
		{ JOY_BUTTON31, "Button 31" },
		{ JOY_BUTTON32, "Button 32" },
	};

	// Unique names for the config files and our pad settings dialog
	const std::unordered_map<u64, std::string> pov_list =
	{
		{ JOY_POVFORWARD,  "POV Up"    },
		{ JOY_POVRIGHT,    "POV Right" },
		{ JOY_POVBACKWARD, "POV Down"  },
		{ JOY_POVLEFT,     "POV Left"  }
	};

	enum mmjoy_axis
	{
		joy_x_pos = 9700,
		joy_x_neg,
		joy_y_pos,
		joy_y_neg,
		joy_z_pos,
		joy_z_neg,
		joy_r_pos,
		joy_r_neg,
		joy_u_pos,
		joy_u_neg,
		joy_v_pos,
		joy_v_neg,
	};

	// Unique names for the config files and our pad settings dialog
	const std::unordered_map<u64, std::string> axis_list =
	{
		{ joy_x_pos, "X+" },
		{ joy_x_neg, "X-" },
		{ joy_y_pos, "Y+" },
		{ joy_y_neg, "Y-" },
		{ joy_z_pos, "Z+" },
		{ joy_z_neg, "Z-" },
		{ joy_r_pos, "R+" },
		{ joy_r_neg, "R-" },
		{ joy_u_pos, "U+" },
		{ joy_u_neg, "U-" },
		{ joy_v_pos, "V+" },
		{ joy_v_neg, "V-" },
	};

	struct MMJOYDevice
	{
		u32 device_id{ 0 };
		std::string device_name{ "" };
		pad_config* config{ nullptr };
		JOYINFOEX device_info;
		JOYCAPS device_caps;
		u64 trigger_left = 0;
		u64 trigger_right = 0;
		std::vector<u64> axis_left  = { 0,0,0,0 };
		std::vector<u64> axis_right = { 0,0,0,0 };
	};

public:
	mm_joystick_handler();
	~mm_joystick_handler();

	bool Init() override;

	std::vector<std::string> ListDevices() override;
	bool bindPadToDevice(std::shared_ptr<Pad> pad, const std::string& device) override;
	void ThreadProc() override;
	void GetNextButtonPress(const std::string& padId, const std::function<void(u16, std::string, std::string, int[])>& callback, const std::function<void(std::string)>& fail_callback, bool get_blacklist = false, const std::vector<std::string>& buttons = {}) override;
	void init_config(pad_config* cfg, const std::string& name) override;

private:
	void TranslateButtonPress(u64 keyCode, bool& pressed, u16& val, bool ignore_threshold = false) override;
	std::unordered_map<u64, u16> GetButtonValues(const JOYINFOEX& js_info, const JOYCAPS& js_caps);
	int GetIDByName(const std::string& name);
	bool GetMMJOYDevice(int index, MMJOYDevice* dev);

	bool is_init = false;
	u32 m_supported_joysticks = 0;

	std::vector<u64> blacklist;
	std::unordered_map<int, MMJOYDevice> m_devices;
	std::vector<std::pair<std::shared_ptr<MMJOYDevice>, std::shared_ptr<Pad>>> bindings;
	std::shared_ptr<MMJOYDevice> m_dev;
};
