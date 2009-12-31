struct __attribute__((packed)) halStore {
	char block_device[DATA_STRING_SIZE];					// block.device
	char block_is_volume[DATA_STRING_SIZE];					// block.is_volume
	char block_major[DATA_STRING_SIZE];					// block.major
	char block_minor[DATA_STRING_SIZE];					// block.minor
	char block_storage_device[DATA_STRING_SIZE];				// block.storage_device

	char ide_channel[DATA_STRING_SIZE];					// ide.channel
	char ide_host[DATA_STRING_SIZE];					// ide.host

	char info_addons[DATA_STRING_SIZE];					// info.addons
	char info_capabilities[DATA_STRING_SIZE];				// info.capabilities
	char info_category[DATA_STRING_SIZE];					// info.category
	char info_interfaces[DATA_STRING_SIZE];					// info.interfaces
	char info_parent[DATA_STRING_SIZE];					// info.parent
	char info_product[DATA_STRING_SIZE];					// info.product
	char info_subsystem[DATA_STRING_SIZE];					// info.subsystem
	char info_udi[DATA_STRING_SIZE];					// info.udi
	char info_vendor[DATA_STRING_SIZE];					// info.vendor
	char info_addons_singleton[DATA_STRING_SIZE];				// info.addons.singleton
	char info_callouts_add[DATA_STRING_SIZE];				// info.callouts.add

	char input_device[DATA_STRING_SIZE];					// input.device
	char input_originating_device[DATA_STRING_SIZE];			// input.originating_device
	char input_product[DATA_STRING_SIZE];					// input.product

	char net_address[DATA_STRING_SIZE];					// net.address
	char net_arp_proto_hw_id[DATA_STRING_SIZE];				// net.arp_proto_hw_id
	char net_interface[DATA_STRING_SIZE];					// net.interface
	char net_originating_device[DATA_STRING_SIZE];				// net.originating_device
	char net_80203_mac_address[DATA_STRING_SIZE];				// net.80203.mac_address

	char pci_device_class[DATA_STRING_SIZE];				// pci.device_class
	char pci_device_protocol[DATA_STRING_SIZE];				// pci.device_protocol
	char pci_device_subclass[DATA_STRING_SIZE];				// pci.device_subclass
	char pci_product_id[DATA_STRING_SIZE];					// pci.product_id
	char pci_subsys_product_id[DATA_STRING_SIZE];				// pci.subsys_product_id
	char pci_subsys_vendor_id[DATA_STRING_SIZE];				// pci.subsys_vendor_id
	char pci_vendor_id[DATA_STRING_SIZE];					// pci.vendor_id

	char platform_id[DATA_STRING_SIZE];					// platform.id

	char pnp_description[DATA_STRING_SIZE];					// pnp.description
	char pnp_id[DATA_STRING_SIZE];						// pnp.id

	char power_management_can_hibernate[DATA_STRING_SIZE];			// power_management.can_hibernate
	char power_management_can_suspend[DATA_STRING_SIZE];			// power_management.can_suspend
	char power_management_can_suspend_hybrid[DATA_STRING_SIZE];		// power_management.can_suspend_hybrid
	char power_management_is_powersave_set[DATA_STRING_SIZE];		// power_management.is_powersave_set
	char power_management_type[DATA_STRING_SIZE];				// power_management.type
	char power_management_quirk_dpms_on[DATA_STRING_SIZE];			// power_management.quirk.dpms_on
	char power_management_quirk_dpms_suspend[DATA_STRING_SIZE];		// power_management.quirk.dpms_suspend
	char power_management_quirk_vbe_post[DATA_STRING_SIZE];			// power_management.quirk.vbe_post
	char power_management_quirk_vbemode_restore[DATA_STRING_SIZE];		// power_management.quirk.vbemode_restore
	char power_management_quirk_vbestate_restore[DATA_STRING_SIZE];		// power_management.quirk.vbestate_restore
	char power_management_quirk_vga_mode_3[DATA_STRING_SIZE];		// power_management.quirk.vga_mode_3

	char processor_can_throttle[DATA_STRING_SIZE];				// processor.can_throttle
	char processor_number[DATA_STRING_SIZE];				// processor.number

	char scsi_host_host[DATA_STRING_SIZE];					// scsi_host.host

	char serio_description[DATA_STRING_SIZE];				// serio.description
	char serio_id[DATA_STRING_SIZE];					// serio.id

	char storage_automount_enabled_hint[DATA_STRING_SIZE];			// storage.automount_enabled_hint
	char storage_bus[DATA_STRING_SIZE];					// storage.bus
	char storage_drive_type[DATA_STRING_SIZE];				// storage.drive_type
	char storage_hotpluggable[DATA_STRING_SIZE];				// storage.hotpluggable
	char storage_media_check_enabled[DATA_STRING_SIZE];			// storage.media_check_enabled
	char storage_model[DATA_STRING_SIZE];					// storage.model
	char storage_no_partitions_hint[DATA_STRING_SIZE];			// storage.no_partitions_hint
	char storage_originating_device[DATA_STRING_SIZE];			// storage.originating_device
	char storage_removable[DATA_STRING_SIZE];				// storage.removable
	char storage_requires_eject[DATA_STRING_SIZE];				// storage.requires_eject
	char storage_size[DATA_STRING_SIZE];					// storage.size
	char storage_vendor[DATA_STRING_SIZE];					// storage.vendor
	char storage_removable_media_available[DATA_STRING_SIZE];		// storage.removable.media_available

	char sound_card[DATA_STRING_SIZE];					// sound.card
	char sound_card_id[DATA_STRING_SIZE];					// sound.card_id
	char sound_originating_device[DATA_STRING_SIZE];			// sound.originating_device

	char system_formfactor[DATA_STRING_SIZE];				// system.formfactor
	char system_board_product[DATA_STRING_SIZE];				// system.board.product
	char system_board_serial[DATA_STRING_SIZE];				// system.board.serial
	char system_board_vendor[DATA_STRING_SIZE];				// system.board.vendor
	char system_board_version[DATA_STRING_SIZE];				// system.board.version
	char system_chassis_manufacturer[DATA_STRING_SIZE];			// system.chassis.manufacturer
	char system_chassis_type[DATA_STRING_SIZE];				// system.chassis.type
	char system_firmware_release_date[DATA_STRING_SIZE];			// system.firmware.release_date
	char system_firmware_vendor[DATA_STRING_SIZE];				// system.firmware.vendor
	char system_firmware_version[DATA_STRING_SIZE];				// system.firmware.version
	char system_hardware_primary_video_product[DATA_STRING_SIZE];		// system.hardware.primary_video.product
	char system_hardware_primary_video_vendor[DATA_STRING_SIZE];		// system.hardware.primary_video.vendor
	char system_hardware_product[DATA_STRING_SIZE];				// system.hardware.product
	char system_hardware_serial[DATA_STRING_SIZE];				// system.hardware.serial
	char system_hardware_uuid[DATA_STRING_SIZE];				// system.hardware.uuid
	char system_hardware_vendor[DATA_STRING_SIZE];				// system.hardware.vendor
	char system_hardware_version[DATA_STRING_SIZE];				// system.hardware.version
	char system_kernel_machine[DATA_STRING_SIZE];				// system.kernel.machine
	char system_kernel_name[DATA_STRING_SIZE];				// system.kernel.name
	char system_kernel_version[DATA_STRING_SIZE];				// system.kernel.version

	char usb_bus_number[DATA_STRING_SIZE];					// usb.bus_number
	char usb_can_wake_up[DATA_STRING_SIZE];					// usb.can_wake_up
	char usb_configuration_value[DATA_STRING_SIZE];				// usb.configuration_value
	char usb_device_class[DATA_STRING_SIZE];				// usb.device_class
	char usb_device_protocol[DATA_STRING_SIZE];				// usb.device_protocol
	char usb_device_revision_bcd[DATA_STRING_SIZE];				// usb.device_revision_bcd
	char usb_device_subclass[DATA_STRING_SIZE];				// usb.device_subclass
	char usb_is_self_powered[DATA_STRING_SIZE];				// usb.is_self_powered
	char usb_max_power[DATA_STRING_SIZE];					// usb.max_power
	char usb_num_configurations[DATA_STRING_SIZE];				// usb.num_configurations
	char usb_num_interfaces[DATA_STRING_SIZE];				// usb.num_interfaces
	char usb_num_ports[DATA_STRING_SIZE];					// usb.num_ports
	char usb_product[DATA_STRING_SIZE];					// usb.product
	char usb_product_id[DATA_STRING_SIZE];					// usb.product_id
	char usb_serial[DATA_STRING_SIZE];					// usb.serial
	char usb_speed[DATA_STRING_SIZE];					// usb.speed
	char usb_vendor[DATA_STRING_SIZE];					// usb.vendor
	char usb_vendor_id[DATA_STRING_SIZE];					// usb.vendor_id
	char usb_version[DATA_STRING_SIZE];					// usb.version
	char usb_interface_class[DATA_STRING_SIZE];				// usb.interface.class
	char usb_interface_number[DATA_STRING_SIZE];				// usb.interface.number
	char usb_interface_protocol[DATA_STRING_SIZE];				// usb.interface.protocol
	char usb_interface_subclass[DATA_STRING_SIZE];				// usb.interface.subclass

	char usb_device_bus_number[DATA_STRING_SIZE];				// usb_device.bus_number
	char usb_device_can_wake_up[DATA_STRING_SIZE];				// usb_device.can_wake_up
	char usb_device_configuration_value[DATA_STRING_SIZE];			// usb_device.configuration_value
	char usb_device_device_class[DATA_STRING_SIZE];				// usb_device.device_class
	char usb_device_device_protocol[DATA_STRING_SIZE];			// usb_device.device_protocol
	char usb_device_device_revision_bcd[DATA_STRING_SIZE];			// usb_device.device_revision_bcd
	char usb_device_device_subclass[DATA_STRING_SIZE];			// usb_device.device_subclass
	char usb_device_is_self_powered[DATA_STRING_SIZE];			// usb_device.is_self_powered
	char usb_device_max_power[DATA_STRING_SIZE];				// usb_device.max_power
	char usb_device_num_configurations[DATA_STRING_SIZE];			// usb_device.num_configurations
	char usb_device_num_interfaces[DATA_STRING_SIZE];			// usb_device.num_interfaces
	char usb_device_num_ports[DATA_STRING_SIZE];				// usb_device.num_ports
	char usb_device_product[DATA_STRING_SIZE];				// usb_device.product
	char usb_device_product_id[DATA_STRING_SIZE];				// usb_device.product_id
	char usb_device_serial[DATA_STRING_SIZE];				// usb_device.serial
	char usb_device_speed[DATA_STRING_SIZE];				// usb_device.speed
	char usb_device_vendor[DATA_STRING_SIZE];				// usb_device.vendor
	char usb_device_vendor_id[DATA_STRING_SIZE];				// usb_device.vendor_id
	char usb_device_version[DATA_STRING_SIZE];				// usb_device.version
};
