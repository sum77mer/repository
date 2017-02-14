#include "stdafx.h"
#include "PCI.h"
#include<vector>
using std::vector;

unsigned int PCI::scan_dev(vector<CFG> &pci_cfg)
{
	unsigned int dll_init=0, dll_status=0;
	DWORD bus = 0;
	WORD dev = 0, fun = 0;
	DWORD addr_temp=0;
	DWORD return_temp = 0;
	struct CFG pci_cfg_temp;
	dll_init = InitializeOls();
	dll_status = GetDllStatus();
	if ((dll_init == 0) || (dll_status != 0))
		AfxMessageBox(_T("Library load wrong!"));
	for(bus=0;bus<256;bus++)
		for(dev=0;dev<32;dev++)
			for (fun = 0; fun < 8; fun++)
			{
				addr_temp = 0x80000000 + (bus << 16) + (dev << 11) + (fun << 8);
				WriteIoPortDword(0xcf8,addr_temp);
				return_temp = ReadIoPortDword(0xcfc);
				if (return_temp != 0xffffffff)
				{
					pci_cfg_temp.bus = bus;
					pci_cfg_temp.dev = dev;
					pci_cfg_temp.fun = fun;
					pci_cfg_temp.addr = addr_temp;
					if (fun == 0)
					{
						addr_temp = (addr_temp & 0xfffffff0) + 0xc;
						WriteIoPortDword(0xcf8, addr_temp);
						return_temp = ReadIoPortDword(0xcfc);
						return_temp = return_temp >> 16;
						if ((return_temp & 0x80) == 0)
							fun = 8;
					}
					addr_temp = pci_cfg_temp.addr;
					WriteIoPortDword(0xcf8,addr_temp);
					if (ReadIoPortDword(0xcfc) != 0xffffffff)
					{
						for (unsigned int i = 0; i < 64; i++)
						{
							WriteIoPortDword(0xcf8, addr_temp);
							pci_cfg_temp.cfg_space_dword[i] = ReadIoPortDword(0xcfc);
							DWORD cfg_dword_to_byte = pci_cfg_temp.cfg_space_dword[i];
							for (unsigned int j = 0; j < 4; j++)
							{
								pci_cfg_temp.cfg_space_byte[i * 4 + j] = cfg_dword_to_byte & 0xff;
								cfg_dword_to_byte = cfg_dword_to_byte >> 8;
							}
							addr_temp += 4;
						}
						pci_cfg.push_back(pci_cfg_temp);
						dev_number++;
					}
					
				}
			}
	DeinitializeOls();
	return dev_number;
}

unsigned int PCI::pci_parser(vector<CFG> &pci_cfg,vector<INFO> &pci_info)
{
	struct INFO pci_info_temp;
	BYTE cap_ptr_temp = 0;
	BYTE cap_id = 0;
	for (auto i:pci_cfg)
	{
		pci_info_temp.vendor_id = i.cfg_space_dword[0]&0xffff;
		pci_info_temp.device_id = (i.cfg_space_dword[0] >> 16) & 0xffff;
		pci_info_temp.command = i.cfg_space_dword[1] & 0xffff;
		pci_info_temp.status = (i.cfg_space_dword[1] >> 16) & 0xffff;
		pci_info_temp.capability_list = i.cfg_space_byte[6] & 0x10;
		pci_info_temp.revision_id = i.cfg_space_dword[2] & 0xff;
		pci_info_temp.base_class = i.cfg_space_byte[0xb];
		pci_info_temp.sub_class = i.cfg_space_byte[0xa];
		pci_info_temp.interface_class = i.cfg_space_byte[0x9];
		pci_info_temp.cacheline_size = i.cfg_space_byte[0xc];
		pci_info_temp.header_type = i.cfg_space_byte[0xe];
		pci_info_temp.interrupt_line = i.cfg_space_byte[0x3c];
		pci_info_temp.interrupt_pin = i.cfg_space_byte[0x3d];
		/*
		if (pci_info_temp.capability_list == 0x10)
		{
			cap_ptr_temp = i.cfg_space_byte[0x34];
			while (cap_ptr_temp != 0)
			{
				cap_id = i.cfg_space_byte[cap_ptr_temp];
				if (cap_id == 0x10)
				{
					pci_info_temp.max_link_speed = i.cfg_space_byte[cap_ptr_temp + 0xC] & 0xf;
					pci_info_temp.max_link_width = (i.cfg_space_byte[cap_ptr_temp + 0xC] & 0xf0) >> 4;
					pci_info_temp.max_link_width &= 0xf;
					pci_info_temp.max_link_width += (i.cfg_space_byte[cap_ptr_temp + 0xD] & 0x3) << 4;

					pci_info_temp.current_link_speed =i.cfg_space_byte[cap_ptr_temp + 0x12] & 0xf;
					pci_info_temp.current_link_width = (i.cfg_space_byte[cap_ptr_temp + 0x12] & 0xf0) >> 4;
					pci_info_temp.current_link_width &= 0xf;
					pci_info_temp.current_link_width += (i.cfg_space_byte[cap_ptr_temp + 0x13] & 0x3) << 4;
				}
				cap_ptr_temp++;
				cap_ptr_temp = i.cfg_space_byte[cap_ptr_temp];
			}
		}
		*/
		switch (pci_info_temp.vendor_id)
		{
			case 0x4b3:
				pci_info_temp.name_string = "IBM"; break;
			case 0x46d: // Logitech
				pci_info_temp.name_string = "Logitech"; break;
			case 0xa5c: // Broadcom
			case 0x1166:
			case 0x14e4:
				pci_info_temp.name_string ="Broadcom"; break;
			case 0xac8: // ASUS
				pci_info_temp.name_string ="ASUS"; break;
			case 0xcf3: // TP-LINK
				pci_info_temp.name_string ="TP-Link"; break;
			case 0x1000:
			case 0x11c1:
			case 0x13c1:
				pci_info_temp.name_string ="LSI"; break;
			case 0x1002: // AMD
			case 0x1014:
			case 0x1022:
				pci_info_temp.name_string ="AMD"; break;
			case 0x102b: // Matrox
				pci_info_temp.name_string ="Matrox"; break;
			case 0x101e: // AMI
			case 0x1529:
				pci_info_temp.name_string ="AMI"; break;
			case 0x1020: // Hitachi
			case 0x1054:
			case 0x1250:
			case 0x1388:
				pci_info_temp.name_string ="Hitachi"; break;
			case 0x1025: // Acer
				pci_info_temp.name_string ="Acer"; break;
			case 0x1028: // Dell
				pci_info_temp.name_string ="Dell"; break;
			case 0x1033: // NEC
			case 0xa200:
				pci_info_temp.name_string ="NEC"; break;
			case 0x104a: // STM
				pci_info_temp.name_string ="STM"; break;
			case 0x104C: // TI
				pci_info_temp.name_string ="TI"; break;
			case 0x106b:
				pci_info_temp.name_string ="Apple"; break;
			case 0x1078:
				pci_info_temp.name_string ="Cyrix"; break;
			case 0x108e:
				pci_info_temp.name_string ="Sun"; break;
			case 0x1095:
				pci_info_temp.name_string ="Silicon Image"; break;
			case 0x1099: // Sumsung Electronic
			case 0x10c3: // Sumsung Semiconductors
				pci_info_temp.name_string ="Sumsung"; break;
			case 0x10ca:
			case 0x119e:
				pci_info_temp.name_string ="Fujitsu"; break;
			case 0x10de: // NVIDIA
				pci_info_temp.name_string ="NVIDIA"; break;
			case 0x10ec: // Realtek
				pci_info_temp.name_string ="Realtek"; break;
			case 0x1106: // VIA
			case 0x1d17:
				pci_info_temp.name_string ="VIA"; break;
			case 0x1114:
				pci_info_temp.name_string ="Atmel"; break;
			case 0x1137:
				pci_info_temp.name_string ="Cisco"; break;
			case 0x113c:
				pci_info_temp.name_string ="Cyclone"; break;
			case 0x115f:
				pci_info_temp.name_string ="Maxtor"; break;
			case 0x1179: // Toshiba
			case 0x13d7:
				pci_info_temp.name_string ="Toshiba"; break;
			case 0x117b: // LG
			case 0x122b:
				pci_info_temp.name_string ="LG"; break;
			case 0x1148:
			case 0x11ab: // Marvell
			case 0x1b4b:
				pci_info_temp.name_string ="Marvell"; break;
			case 0x11ad: // Lite-On
				pci_info_temp.name_string ="Lite-On"; break;
			case 0x11b7: // Motorola
				pci_info_temp.name_string ="Motorola"; break;
			case 0x1260:
				pci_info_temp.name_string ="Intersil"; break;
			case 0x12d1: // Huawei
				pci_info_temp.name_string ="Huawei"; break;
			case 0x1363:
				pci_info_temp.name_string ="Phoenix"; break;
			case 0x13b5:
				pci_info_temp.name_string ="ARM"; break;
			case 0x13bd:
				pci_info_temp.name_string ="SHARP"; break;
			case 0x1462:
				pci_info_temp.name_string ="MSI"; break;
			case 0x153f:
				pci_info_temp.name_string ="MIPS"; break;
			case 0x1574:
				pci_info_temp.name_string ="Fairchild"; break;
			case 0x15b7: // Sandisk
				pci_info_temp.name_string ="Sandisk"; break;
			case 0x2646: // Kingston
				pci_info_temp.name_string ="Kingston"; break;
			case 0x1344:
			case 0xc0a9: // Micron?/Crutial
				pci_info_temp.name_string ="Micron/Crutial"; break;
			case 0x5333:
				pci_info_temp.name_string ="S3"; break;
			case 0x1b21:
			case 0x6945:
				pci_info_temp.name_string ="ASMedia"; break;
			case 0x104d:
			case 0xa304: // Sony
				pci_info_temp.name_string ="Sony"; break;
			case 0x163c:
			case 0x8086: // Intel
			case 0x8087:
				pci_info_temp.name_string ="Intel"; break;
			case 0x9004:
			case 0x9005:
				pci_info_temp.name_string ="Adaptec"; break;
			default:
				pci_info_temp.name_string ="Unknown"; break;
		}
		switch (pci_info_temp.base_class)
		{
			case 0x0: // Device was built before Class Code definitions	
				switch (pci_info_temp.sub_class)
				{
					case 0x0: // Currently implemented devices
						pci_info_temp.name_string+=" Implemented";
						break;
					case 0x1: // VGA-compatible device
						pci_info_temp.name_string+=" VGA-compatible";
						break;
					default:
						pci_info_temp.name_string+=" Lagacy";
						break;
				}
				break;
			case 0x1: // Mass Storage Controller 
				switch (pci_info_temp.sub_class)
					{
						case 0x0: // SCSI bus controller
						pci_info_temp.name_string+=" SCSI bus controller";
						break;
					case 0x1: // IDE controller
						pci_info_temp.name_string+=" IDE controller";
						break;
					case 0x2: // Floppy disk controller
						pci_info_temp.name_string+=" Floppy disk controller";
						break;
					case 0x3:
						pci_info_temp.name_string+=" IPI bus controller";
						break;
					case 0x4:
						pci_info_temp.name_string+=" RAID controller";
						break;
					case 0x5:
						pci_info_temp.name_string+=" ATA controller";
						break;
					case 0x6:
						pci_info_temp.name_string+=" SATA controller";
						break;
					case 0x7:
						pci_info_temp.name_string+=" SAS controller";
						break;
					case 0x80:
						pci_info_temp.name_string+=" Mass storage controller";
						break;
					default:
						pci_info_temp.name_string+=" Mass storage controller";
						break;
				}
				break;
			case 0x2: // Network Controller 
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" Ethernet controller";
						break;
					case 0x1:
						pci_info_temp.name_string+=" Token Ring controller";
						break;
					case 0x2:
						pci_info_temp.name_string+=" FDDI controller";
						break;
					case 0x3:
						pci_info_temp.name_string+=" ATM controller";
						break;
					case 0x4:
						pci_info_temp.name_string+=" ISDN controller";
						break;
					case 0x5:
						pci_info_temp.name_string+=" WorldFip controller";
						break;
					case 0x6:
						pci_info_temp.name_string+=" PICMG 2.14 Multi Computing";
						break;
					case 0x80:
						pci_info_temp.name_string+=" network controller";
						break;
					default:
						pci_info_temp.name_string+=" network controller";
						break;
				}
					break;
			case 0x3: // Display Controller 
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" VGA controller";
						break;
					case 0x1:
						pci_info_temp.name_string+=" XGA controller";
						break;
					case 0x2:
						pci_info_temp.name_string+=" 3D controller";
						break;
					case 0x80:
						pci_info_temp.name_string+=" display controller";
						break;
					default:
						pci_info_temp.name_string+=" display controller";
						break;
				}
				break;
			case 0x4: // Multimedia Device 
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" Video device";
						break;
					case 0x1:
						pci_info_temp.name_string+=" Audio device";
						break;
					case 0x2:
						pci_info_temp.name_string+=" Computer telephony device";
						break;
					case 0x80:
						pci_info_temp.name_string+=" multimedia device";
						break;
					default:
						pci_info_temp.name_string+=" multidedia device";
						break;
				}
				break;
			case 0x5: // Memory Controller 
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" RAM controller";
						break;
					case 0x1:
						pci_info_temp.name_string+=" Flash controller";
						break;
					case 0x80:
						pci_info_temp.name_string+=" memory controller";
						break;
					default:
						pci_info_temp.name_string+=" memory controller";
						break;
				}
				break;
			case 0x6: // Bridge Device 
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" Host bridge";
						break;
					case 0x1:
						pci_info_temp.name_string+=" ISA bridge";
						break;
					case 0x2:
						pci_info_temp.name_string+=" EISA bridge";
						break;
					case 0x3:
						pci_info_temp.name_string+=" MCA bridge";
						break;
					case 0x4:
						pci_info_temp.name_string+=" PCI-to-PCI bridge";
						break;
					case 0x5:
						pci_info_temp.name_string+=" PCMCIA bridge";
						break;
					case 0x6:
						pci_info_temp.name_string+=" NuBus bridge";
						break;
					case 0x7:
						pci_info_temp.name_string+=" CardBus bridge";
						break;
					case 0x8:
						pci_info_temp.name_string+=" RACEway bridge";
						break;
					case 0x9:
						pci_info_temp.name_string+=" Semi-transparent PCI-to-PCI";
						break;
					case 0xa:
						pci_info_temp.name_string+=" InfiniBand-to-PCI bridge";
						break;
					case 0x80:
						pci_info_temp.name_string+=" bridge device";
						break;
					default:
						pci_info_temp.name_string+=" bridge device";
						break;
				}
				break;
			case 0x7: // Simple Communication Controller 
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" serial controller";
						break;
					case 0x1:
						pci_info_temp.name_string+=" Parallel port/controller";
						break;
					case 0x2:
						pci_info_temp.name_string+=" Multiport serial controller";
						break;
					case 0x3:
						pci_info_temp.name_string+=" Generic/Hayes modem";
						break;
					case 0x4:
						pci_info_temp.name_string+=" GPIB controller";
						break;
					case 0x5:
						pci_info_temp.name_string+=" Smart Card";
						break;
					case 0x80:
						pci_info_temp.name_string+=" communications device";
						break;
					default:
						pci_info_temp.name_string+=" communication device";
						break;
				}
				break;
			case 0x8: // Base System Peripherals
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" PIC/APIC";
						break;
					case 0x1:
						pci_info_temp.name_string+=" DMA controller";
						break;
					case 0x2:
						pci_info_temp.name_string+=" System timer";
						break;
					case 0x3:
						pci_info_temp.name_string+=" RTC controller";
						break;
					case 0x4:
						pci_info_temp.name_string+=" PCI Hot-plug controller";
						break;
					case 0x5:
						pci_info_temp.name_string+=" SD Host controller";
						break;
					case 0x80:
						pci_info_temp.name_string+=" system peripheral";
						break;
					default:
						pci_info_temp.name_string+=" system peripheral";
						break;
				}
				break;
			case 0x9: // Input Device 
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" Keyboard controller";
						break;
					case 0x1:
						pci_info_temp.name_string+=" Digitizer(pen)";
						break;
					case 0x2:
						pci_info_temp.name_string+=" Mouse controller";
						break;
					case 0x3:
						pci_info_temp.name_string+=" Scanner controller";
						break;
					case 0x4:
						pci_info_temp.name_string+=" Gameport controller";
						break;
					case 0x80:
						pci_info_temp.name_string+=" input controller";
						break;
					default:
						pci_info_temp.name_string+=" Input device";
						break;
				}
				break;
			case 0xa: // Docking Stations
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" Generic docking station";
						break;
					case 0x1:
						pci_info_temp.name_string+=" docking station";
						break;
					default:
						pci_info_temp.name_string+=" docking station";
						break;
				}
				break;
			case 0xb: // Processors
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" 386";
						break;
					case 0x1:
						pci_info_temp.name_string+=" 486";
						break;
					case 0x2:
						pci_info_temp.name_string+=" Pentium";
						break;
					case 0x10:
						pci_info_temp.name_string+=" Alpha";
						break;
					case 0x20:
						pci_info_temp.name_string+=" PowerPC";
						break;
					case 0x30:
						pci_info_temp.name_string+=" MIPS";
						break;
					case 0x40:
						pci_info_temp.name_string+=" Co-processor";
						break;
					default:
						pci_info_temp.name_string+=" Processor";
						break;
				}
				break;
			case 0xc: // Serial Bus Controller
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" IEEE 1394";
						break;
					case 0x1:
						pci_info_temp.name_string+=" ACCESS.bus";
						break;
					case 0x2:
						pci_info_temp.name_string+=" SSA";
						break;
					case 0x3:
						switch (pci_info_temp.interface_class)
						{
						case 0x0:
							pci_info_temp.name_string+=" UHCI controller";
							break;
						case 0x10:
							pci_info_temp.name_string+=" OHCI controller";
							break;
						case 0x20:
							pci_info_temp.name_string+=" EHCI controller";
							break;
						case 0x30:
							pci_info_temp.name_string+=" xHCI controller";
							break;
						case 0x80:
							pci_info_temp.name_string+=" USB controller";
							break;
						case 0xfe:
							pci_info_temp.name_string+=" USB device";
							break;
						default:
							pci_info_temp.name_string+=" USB controller";
							break;
						}
						break;
					case 0x4:
						pci_info_temp.name_string+=" Fibre Channel";
						break;
					case 0x5:
						pci_info_temp.name_string+=" SMBus";
						break;
					case 0x6:
						pci_info_temp.name_string+=" InfiniBand";
						break;
					case 0x7:
						pci_info_temp.name_string+=" IPMI Interface";
						break;
					case 0x8:
						pci_info_temp.name_string+=" SERCOS Interface";
						break;
					case 0x9:
						pci_info_temp.name_string+=" CANbus";
						break;
					default:
						pci_info_temp.name_string+=" Serial Bus Controller";
						break;
				}
				break;
			case 0xd: // Wireless Controller
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" iRDA controller";
						break;
					case 0x1:
						pci_info_temp.name_string+=" Consumer IR controller";
						break;
					case 0x10:
						pci_info_temp.name_string+=" RF controller";
						break;
					case 0x11:
						pci_info_temp.name_string+=" Bluetooth";
						break;
					case 0x12:
						pci_info_temp.name_string+=" Broadband";
						break;
					case 0x20:
						pci_info_temp.name_string+=" Ethernet(802.11.a)";
						break;
					case 0x21:
						pci_info_temp.name_string+=" Ethernet(802.11.b)";
						break;
					case 0x80:
						pci_info_temp.name_string+=" wireless controller";
						break;
					default:
						pci_info_temp.name_string+=" wireless controller";
						break;
				}
				break;
			case 0xe: // Intelligent IO Controller 
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" Message FIFO";
						break;
					default:
						pci_info_temp.name_string+=" IO controller";
						break;
				}
				break;
			case 0xf: // Satellite Communication
				switch (pci_info_temp.sub_class)
				{
					case 0x1:
						pci_info_temp.name_string+=" TV Satellite";
						break;
					case 0x2:
						pci_info_temp.name_string+=" Audio Satellite";
						break;
					case 0x3:
						pci_info_temp.name_string+=" Voice Satellite";
						break;
					case 0x4:
						pci_info_temp.name_string+=" Data Satellite";
						break;
					default:
						pci_info_temp.name_string+=" Satallite";
						break;
				}
				break;
			case 0x10: // Encryption / Decryption controller
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" Netword and computing en/decryption";
						break;
					case 0x1:
						pci_info_temp.name_string+=" Entertainment en/decryption";
						break;
					case 0x80:
						pci_info_temp.name_string+=" en/decryption";
						break;
					default:
						pci_info_temp.name_string+=" en/decryption";
						break;
				}
				break;
			case 0x11: // Data accquisition signal processing controller
				switch (pci_info_temp.sub_class)
				{
					case 0x0:
						pci_info_temp.name_string+=" DPIO modules";
						break;
					case 0x1:
						pci_info_temp.name_string+=" Performance counters";
						break;
					case 0x10:
						pci_info_temp.name_string+=" Time and frequency test/measurement";
						break;
					case 0x20:
						pci_info_temp.name_string+=" Management card";
						break;
					case 0x80:
						pci_info_temp.name_string+=" data/signal controller";
						break;
					default:
						pci_info_temp.name_string+=" data/signal controller";
						break;
				}
				break;
			default: // Undefined base class
				pci_info_temp.name_string+=" Undefiend Base Class";
				break;
			}
		pci_info.push_back(pci_info_temp);
		
	}
	return 0;
}
unsigned int PCI::pci_parser(vector<CFG_SHORT> &pci_cfg, vector<INFO> &pci_info)
{
	struct INFO pci_info_temp;
	BYTE cap_ptr_temp = 0;
	BYTE cap_id = 0;
	for (auto i : pci_cfg)
	{
		pci_info_temp.vendor_id = i.cfg_space_dword[0] & 0xffff;
		pci_info_temp.device_id = (i.cfg_space_dword[0] >> 16) & 0xffff;
		pci_info_temp.command = i.cfg_space_dword[1] & 0xffff;
		pci_info_temp.status = (i.cfg_space_dword[1] >> 16) & 0xffff;
		pci_info_temp.capability_list = i.cfg_space_byte[6] & 0x10;
		pci_info_temp.revision_id = i.cfg_space_dword[2] & 0xff;
		pci_info_temp.base_class = i.cfg_space_byte[0xb];
		pci_info_temp.sub_class = i.cfg_space_byte[0xa];
		pci_info_temp.interface_class = i.cfg_space_byte[0x9];
		pci_info_temp.cacheline_size = i.cfg_space_byte[0xc];
		pci_info_temp.header_type = i.cfg_space_byte[0xe];
		pci_info_temp.interrupt_line = i.cfg_space_byte[0x3c];
		pci_info_temp.interrupt_pin = i.cfg_space_byte[0x3d];
		/*
		if (pci_info_temp.capability_list == 0x10)
		{
		cap_ptr_temp = i.cfg_space_byte[0x34];
		while (cap_ptr_temp != 0)
		{
		cap_id = i.cfg_space_byte[cap_ptr_temp];
		if (cap_id == 0x10)
		{
		pci_info_temp.max_link_speed = i.cfg_space_byte[cap_ptr_temp + 0xC] & 0xf;
		pci_info_temp.max_link_width = (i.cfg_space_byte[cap_ptr_temp + 0xC] & 0xf0) >> 4;
		pci_info_temp.max_link_width &= 0xf;
		pci_info_temp.max_link_width += (i.cfg_space_byte[cap_ptr_temp + 0xD] & 0x3) << 4;

		pci_info_temp.current_link_speed =i.cfg_space_byte[cap_ptr_temp + 0x12] & 0xf;
		pci_info_temp.current_link_width = (i.cfg_space_byte[cap_ptr_temp + 0x12] & 0xf0) >> 4;
		pci_info_temp.current_link_width &= 0xf;
		pci_info_temp.current_link_width += (i.cfg_space_byte[cap_ptr_temp + 0x13] & 0x3) << 4;
		}
		cap_ptr_temp++;
		cap_ptr_temp = i.cfg_space_byte[cap_ptr_temp];
		}
		}
		*/
		switch (pci_info_temp.vendor_id)
		{
		case 0x4b3:
			pci_info_temp.name_string = "IBM"; break;
		case 0x46d: // Logitech
			pci_info_temp.name_string = "Logitech"; break;
		case 0xa5c: // Broadcom
		case 0x1166:
		case 0x14e4:
			pci_info_temp.name_string = "Broadcom"; break;
		case 0xac8: // ASUS
			pci_info_temp.name_string = "ASUS"; break;
		case 0xcf3: // TP-LINK
			pci_info_temp.name_string = "TP-Link"; break;
		case 0x1000:
		case 0x11c1:
		case 0x13c1:
			pci_info_temp.name_string = "LSI"; break;
		case 0x1002: // AMD
		case 0x1014:
		case 0x1022:
			pci_info_temp.name_string = "AMD"; break;
		case 0x102b: // Matrox
			pci_info_temp.name_string = "Matrox"; break;
		case 0x101e: // AMI
		case 0x1529:
			pci_info_temp.name_string = "AMI"; break;
		case 0x1020: // Hitachi
		case 0x1054:
		case 0x1250:
		case 0x1388:
			pci_info_temp.name_string = "Hitachi"; break;
		case 0x1025: // Acer
			pci_info_temp.name_string = "Acer"; break;
		case 0x1028: // Dell
			pci_info_temp.name_string = "Dell"; break;
		case 0x1033: // NEC
		case 0xa200:
			pci_info_temp.name_string = "NEC"; break;
		case 0x104a: // STM
			pci_info_temp.name_string = "STM"; break;
		case 0x104C: // TI
			pci_info_temp.name_string = "TI"; break;
		case 0x106b:
			pci_info_temp.name_string = "Apple"; break;
		case 0x1078:
			pci_info_temp.name_string = "Cyrix"; break;
		case 0x108e:
			pci_info_temp.name_string = "Sun"; break;
		case 0x1095:
			pci_info_temp.name_string = "Silicon Image"; break;
		case 0x1099: // Sumsung Electronic
		case 0x10c3: // Sumsung Semiconductors
			pci_info_temp.name_string = "Sumsung"; break;
		case 0x10ca:
		case 0x119e:
			pci_info_temp.name_string = "Fujitsu"; break;
		case 0x10de: // NVIDIA
			pci_info_temp.name_string = "NVIDIA"; break;
		case 0x10ec: // Realtek
			pci_info_temp.name_string = "Realtek"; break;
		case 0x1106: // VIA
		case 0x1d17:
			pci_info_temp.name_string = "VIA"; break;
		case 0x1114:
			pci_info_temp.name_string = "Atmel"; break;
		case 0x1137:
			pci_info_temp.name_string = "Cisco"; break;
		case 0x113c:
			pci_info_temp.name_string = "Cyclone"; break;
		case 0x115f:
			pci_info_temp.name_string = "Maxtor"; break;
		case 0x1179: // Toshiba
		case 0x13d7:
			pci_info_temp.name_string = "Toshiba"; break;
		case 0x117b: // LG
		case 0x122b:
			pci_info_temp.name_string = "LG"; break;
		case 0x1148:
		case 0x11ab: // Marvell
		case 0x1b4b:
			pci_info_temp.name_string = "Marvell"; break;
		case 0x11ad: // Lite-On
			pci_info_temp.name_string = "Lite-On"; break;
		case 0x11b7: // Motorola
			pci_info_temp.name_string = "Motorola"; break;
		case 0x1260:
			pci_info_temp.name_string = "Intersil"; break;
		case 0x12d1: // Huawei
			pci_info_temp.name_string = "Huawei"; break;
		case 0x1363:
			pci_info_temp.name_string = "Phoenix"; break;
		case 0x13b5:
			pci_info_temp.name_string = "ARM"; break;
		case 0x13bd:
			pci_info_temp.name_string = "SHARP"; break;
		case 0x1462:
			pci_info_temp.name_string = "MSI"; break;
		case 0x153f:
			pci_info_temp.name_string = "MIPS"; break;
		case 0x1574:
			pci_info_temp.name_string = "Fairchild"; break;
		case 0x15b7: // Sandisk
			pci_info_temp.name_string = "Sandisk"; break;
		case 0x2646: // Kingston
			pci_info_temp.name_string = "Kingston"; break;
		case 0x1344:
		case 0xc0a9: // Micron?/Crutial
			pci_info_temp.name_string = "Micron/Crutial"; break;
		case 0x5333:
			pci_info_temp.name_string = "S3"; break;
		case 0x1b21:
		case 0x6945:
			pci_info_temp.name_string = "ASMedia"; break;
		case 0x104d:
		case 0xa304: // Sony
			pci_info_temp.name_string = "Sony"; break;
		case 0x163c:
		case 0x8086: // Intel
		case 0x8087:
			pci_info_temp.name_string = "Intel"; break;
		case 0x9004:
		case 0x9005:
			pci_info_temp.name_string = "Adaptec"; break;
		default:
			pci_info_temp.name_string = "Unknown"; break;
		}
		switch (pci_info_temp.base_class)
		{
		case 0x0: // Device was built before Class Code definitions	
			switch (pci_info_temp.sub_class)
			{
			case 0x0: // Currently implemented devices
				pci_info_temp.name_string += " Implemented";
				break;
			case 0x1: // VGA-compatible device
				pci_info_temp.name_string += " VGA-compatible";
				break;
			default:
				pci_info_temp.name_string += " Lagacy";
				break;
			}
			break;
		case 0x1: // Mass Storage Controller 
			switch (pci_info_temp.sub_class)
			{
			case 0x0: // SCSI bus controller
				pci_info_temp.name_string += " SCSI bus controller";
				break;
			case 0x1: // IDE controller
				pci_info_temp.name_string += " IDE controller";
				break;
			case 0x2: // Floppy disk controller
				pci_info_temp.name_string += " Floppy disk controller";
				break;
			case 0x3:
				pci_info_temp.name_string += " IPI bus controller";
				break;
			case 0x4:
				pci_info_temp.name_string += " RAID controller";
				break;
			case 0x5:
				pci_info_temp.name_string += " ATA controller";
				break;
			case 0x6:
				pci_info_temp.name_string += " SATA controller";
				break;
			case 0x7:
				pci_info_temp.name_string += " SAS controller";
				break;
			case 0x80:
				pci_info_temp.name_string += " Mass storage controller";
				break;
			default:
				pci_info_temp.name_string += " Mass storage controller";
				break;
			}
			break;
		case 0x2: // Network Controller 
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " Ethernet controller";
				break;
			case 0x1:
				pci_info_temp.name_string += " Token Ring controller";
				break;
			case 0x2:
				pci_info_temp.name_string += " FDDI controller";
				break;
			case 0x3:
				pci_info_temp.name_string += " ATM controller";
				break;
			case 0x4:
				pci_info_temp.name_string += " ISDN controller";
				break;
			case 0x5:
				pci_info_temp.name_string += " WorldFip controller";
				break;
			case 0x6:
				pci_info_temp.name_string += " PICMG 2.14 Multi Computing";
				break;
			case 0x80:
				pci_info_temp.name_string += " network controller";
				break;
			default:
				pci_info_temp.name_string += " network controller";
				break;
			}
			break;
		case 0x3: // Display Controller 
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " VGA controller";
				break;
			case 0x1:
				pci_info_temp.name_string += " XGA controller";
				break;
			case 0x2:
				pci_info_temp.name_string += " 3D controller";
				break;
			case 0x80:
				pci_info_temp.name_string += " display controller";
				break;
			default:
				pci_info_temp.name_string += " display controller";
				break;
			}
			break;
		case 0x4: // Multimedia Device 
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " Video device";
				break;
			case 0x1:
				pci_info_temp.name_string += " Audio device";
				break;
			case 0x2:
				pci_info_temp.name_string += " Computer telephony device";
				break;
			case 0x80:
				pci_info_temp.name_string += " multimedia device";
				break;
			default:
				pci_info_temp.name_string += " multidedia device";
				break;
			}
			break;
		case 0x5: // Memory Controller 
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " RAM controller";
				break;
			case 0x1:
				pci_info_temp.name_string += " Flash controller";
				break;
			case 0x80:
				pci_info_temp.name_string += " memory controller";
				break;
			default:
				pci_info_temp.name_string += " memory controller";
				break;
			}
			break;
		case 0x6: // Bridge Device 
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " Host bridge";
				break;
			case 0x1:
				pci_info_temp.name_string += " ISA bridge";
				break;
			case 0x2:
				pci_info_temp.name_string += " EISA bridge";
				break;
			case 0x3:
				pci_info_temp.name_string += " MCA bridge";
				break;
			case 0x4:
				pci_info_temp.name_string += " PCI-to-PCI bridge";
				break;
			case 0x5:
				pci_info_temp.name_string += " PCMCIA bridge";
				break;
			case 0x6:
				pci_info_temp.name_string += " NuBus bridge";
				break;
			case 0x7:
				pci_info_temp.name_string += " CardBus bridge";
				break;
			case 0x8:
				pci_info_temp.name_string += " RACEway bridge";
				break;
			case 0x9:
				pci_info_temp.name_string += " Semi-transparent PCI-to-PCI";
				break;
			case 0xa:
				pci_info_temp.name_string += " InfiniBand-to-PCI bridge";
				break;
			case 0x80:
				pci_info_temp.name_string += " bridge device";
				break;
			default:
				pci_info_temp.name_string += " bridge device";
				break;
			}
			break;
		case 0x7: // Simple Communication Controller 
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " serial controller";
				break;
			case 0x1:
				pci_info_temp.name_string += " Parallel port/controller";
				break;
			case 0x2:
				pci_info_temp.name_string += " Multiport serial controller";
				break;
			case 0x3:
				pci_info_temp.name_string += " Generic/Hayes modem";
				break;
			case 0x4:
				pci_info_temp.name_string += " GPIB controller";
				break;
			case 0x5:
				pci_info_temp.name_string += " Smart Card";
				break;
			case 0x80:
				pci_info_temp.name_string += " communications device";
				break;
			default:
				pci_info_temp.name_string += " communication device";
				break;
			}
			break;
		case 0x8: // Base System Peripherals
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " PIC/APIC";
				break;
			case 0x1:
				pci_info_temp.name_string += " DMA controller";
				break;
			case 0x2:
				pci_info_temp.name_string += " System timer";
				break;
			case 0x3:
				pci_info_temp.name_string += " RTC controller";
				break;
			case 0x4:
				pci_info_temp.name_string += " PCI Hot-plug controller";
				break;
			case 0x5:
				pci_info_temp.name_string += " SD Host controller";
				break;
			case 0x80:
				pci_info_temp.name_string += " system peripheral";
				break;
			default:
				pci_info_temp.name_string += " system peripheral";
				break;
			}
			break;
		case 0x9: // Input Device 
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " Keyboard controller";
				break;
			case 0x1:
				pci_info_temp.name_string += " Digitizer(pen)";
				break;
			case 0x2:
				pci_info_temp.name_string += " Mouse controller";
				break;
			case 0x3:
				pci_info_temp.name_string += " Scanner controller";
				break;
			case 0x4:
				pci_info_temp.name_string += " Gameport controller";
				break;
			case 0x80:
				pci_info_temp.name_string += " input controller";
				break;
			default:
				pci_info_temp.name_string += " Input device";
				break;
			}
			break;
		case 0xa: // Docking Stations
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " Generic docking station";
				break;
			case 0x1:
				pci_info_temp.name_string += " docking station";
				break;
			default:
				pci_info_temp.name_string += " docking station";
				break;
			}
			break;
		case 0xb: // Processors
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " 386";
				break;
			case 0x1:
				pci_info_temp.name_string += " 486";
				break;
			case 0x2:
				pci_info_temp.name_string += " Pentium";
				break;
			case 0x10:
				pci_info_temp.name_string += " Alpha";
				break;
			case 0x20:
				pci_info_temp.name_string += " PowerPC";
				break;
			case 0x30:
				pci_info_temp.name_string += " MIPS";
				break;
			case 0x40:
				pci_info_temp.name_string += " Co-processor";
				break;
			default:
				pci_info_temp.name_string += " Processor";
				break;
			}
			break;
		case 0xc: // Serial Bus Controller
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " IEEE 1394";
				break;
			case 0x1:
				pci_info_temp.name_string += " ACCESS.bus";
				break;
			case 0x2:
				pci_info_temp.name_string += " SSA";
				break;
			case 0x3:
				switch (pci_info_temp.interface_class)
				{
				case 0x0:
					pci_info_temp.name_string += " UHCI controller";
					break;
				case 0x10:
					pci_info_temp.name_string += " OHCI controller";
					break;
				case 0x20:
					pci_info_temp.name_string += " EHCI controller";
					break;
				case 0x30:
					pci_info_temp.name_string += " xHCI controller";
					break;
				case 0x80:
					pci_info_temp.name_string += " USB controller";
					break;
				case 0xfe:
					pci_info_temp.name_string += " USB device";
					break;
				default:
					pci_info_temp.name_string += " USB controller";
					break;
				}
				break;
			case 0x4:
				pci_info_temp.name_string += " Fibre Channel";
				break;
			case 0x5:
				pci_info_temp.name_string += " SMBus";
				break;
			case 0x6:
				pci_info_temp.name_string += " InfiniBand";
				break;
			case 0x7:
				pci_info_temp.name_string += " IPMI Interface";
				break;
			case 0x8:
				pci_info_temp.name_string += " SERCOS Interface";
				break;
			case 0x9:
				pci_info_temp.name_string += " CANbus";
				break;
			default:
				pci_info_temp.name_string += " Serial Bus Controller";
				break;
			}
			break;
		case 0xd: // Wireless Controller
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " iRDA controller";
				break;
			case 0x1:
				pci_info_temp.name_string += " Consumer IR controller";
				break;
			case 0x10:
				pci_info_temp.name_string += " RF controller";
				break;
			case 0x11:
				pci_info_temp.name_string += " Bluetooth";
				break;
			case 0x12:
				pci_info_temp.name_string += " Broadband";
				break;
			case 0x20:
				pci_info_temp.name_string += " Ethernet(802.11.a)";
				break;
			case 0x21:
				pci_info_temp.name_string += " Ethernet(802.11.b)";
				break;
			case 0x80:
				pci_info_temp.name_string += " wireless controller";
				break;
			default:
				pci_info_temp.name_string += " wireless controller";
				break;
			}
			break;
		case 0xe: // Intelligent IO Controller 
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " Message FIFO";
				break;
			default:
				pci_info_temp.name_string += " IO controller";
				break;
			}
			break;
		case 0xf: // Satellite Communication
			switch (pci_info_temp.sub_class)
			{
			case 0x1:
				pci_info_temp.name_string += " TV Satellite";
				break;
			case 0x2:
				pci_info_temp.name_string += " Audio Satellite";
				break;
			case 0x3:
				pci_info_temp.name_string += " Voice Satellite";
				break;
			case 0x4:
				pci_info_temp.name_string += " Data Satellite";
				break;
			default:
				pci_info_temp.name_string += " Satallite";
				break;
			}
			break;
		case 0x10: // Encryption / Decryption controller
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " Netword and computing en/decryption";
				break;
			case 0x1:
				pci_info_temp.name_string += " Entertainment en/decryption";
				break;
			case 0x80:
				pci_info_temp.name_string += " en/decryption";
				break;
			default:
				pci_info_temp.name_string += " en/decryption";
				break;
			}
			break;
		case 0x11: // Data accquisition signal processing controller
			switch (pci_info_temp.sub_class)
			{
			case 0x0:
				pci_info_temp.name_string += " DPIO modules";
				break;
			case 0x1:
				pci_info_temp.name_string += " Performance counters";
				break;
			case 0x10:
				pci_info_temp.name_string += " Time and frequency test/measurement";
				break;
			case 0x20:
				pci_info_temp.name_string += " Management card";
				break;
			case 0x80:
				pci_info_temp.name_string += " data/signal controller";
				break;
			default:
				pci_info_temp.name_string += " data/signal controller";
				break;
			}
			break;
		default: // Undefined base class
			pci_info_temp.name_string += " Undefiend Base Class";
			break;
		}
		pci_info.push_back(pci_info_temp);

	}
	return 0;
}

unsigned int PCI::scan_dev(vector<CFG_SHORT> &pci_cfg,vector<unsigned int> &addr)
{
	unsigned int dll_init = 0, dll_status = 0;
	unsigned int addr_temp = 0;
	DWORD return_temp = 0;
	struct CFG_SHORT pci_cfg_temp;
	dll_init = InitializeOls();
	dll_status = GetDllStatus();
	if ((dll_init == 0) || (dll_status != 0))
		AfxMessageBox(_T("Library load wrong!"));
	for (auto q:addr)
	{
		addr_temp = q;
		WriteIoPortDword(0xcf8, addr_temp);
		return_temp = ReadIoPortDword(0xcfc);
		if (return_temp != 0xffffffff)
		{
			pci_cfg_temp.addr = addr_temp;
			
			for (unsigned int i = 0; i < 64; i++)
			{
			WriteIoPortDword(0xcf8, addr_temp);
			pci_cfg_temp.cfg_space_dword[i] = ReadIoPortDword(0xcfc);
			DWORD cfg_dword_to_byte = pci_cfg_temp.cfg_space_dword[i];
			for (unsigned int j = 0; j < 4; j++)
			{
			pci_cfg_temp.cfg_space_byte[i * 4 + j] = cfg_dword_to_byte & 0xff;
			cfg_dword_to_byte = cfg_dword_to_byte >> 8;
			}
			addr_temp += 4;
			}
			pci_cfg.push_back(pci_cfg_temp);
			
			
		}
	}
	DeinitializeOls();
	return 6;
}
