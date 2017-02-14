#pragma once
#include<vector>
using std::vector;
class PCI
{
public:

	PCI()
	{
	}

	virtual ~PCI()
	{
	}
	struct CFG
	{
		DWORD bus;
		WORD dev;
		WORD fun;
		DWORD addr;
		BYTE cfg_space_byte[256];
		DWORD cfg_space_dword[64];
	};
	struct CFG_SHORT
	{
		DWORD addr;
		BYTE cfg_space_byte[256];
		DWORD cfg_space_dword[64];
	};
	struct INFO
	{
		WORD vendor_id;
		WORD device_id;
		WORD command;
		WORD status;
		unsigned int capability_list;
		BYTE revision_id;
		BYTE base_class;
		BYTE sub_class;
		BYTE interface_class;
		BYTE cacheline_size;
		BYTE header_type;//device type, type 0 PCI agent, type 1 PCI bridge, type 2 PCI cardbus bridge
		BYTE interrupt_line;
		BYTE interrupt_pin;
		unsigned int max_link_speed;
		unsigned int max_link_width;
		unsigned int current_link_speed;
		unsigned int current_link_width;
		CString name_string;
	};
	unsigned int dev_number;
	vector<CFG> pci_cfg;
	vector<CFG_SHORT> pci_cfg_short;
	vector<INFO> pci_info;
	unsigned int scan_dev(vector<CFG> &pci_cfg);
	unsigned int scan_dev(vector<CFG_SHORT> &pci_cfg, vector<unsigned int> &addr);
	unsigned int pci_parser(vector<CFG> &pci_cfg,vector<INFO> &pci_info);
	unsigned int pci_parser(vector<CFG_SHORT> &pci_cfg, vector<INFO> &pci_info);
	
};

