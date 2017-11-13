#undef TRACE_SYSTEM
#define TRACE_SYSTEM hyperv

#if !defined(_HV_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#define _HV_TRACE_H

#include <linux/tracepoint.h>

DECLARE_EVENT_CLASS(vmbus_hdr_msg,
	TP_PROTO(const struct vmbus_channel_message_header *hdr),
	TP_ARGS(hdr),
	TP_STRUCT__entry(__field(unsigned int, msgtype)),
	TP_fast_assign(__entry->msgtype = hdr->msgtype;),
	TP_printk("msgtype=%u", __entry->msgtype)
);

DEFINE_EVENT(vmbus_hdr_msg, vmbus_on_msg_dpc,
	TP_PROTO(const struct vmbus_channel_message_header *hdr),
	TP_ARGS(hdr)
);

DEFINE_EVENT(vmbus_hdr_msg, vmbus_on_message,
	TP_PROTO(const struct vmbus_channel_message_header *hdr),
	TP_ARGS(hdr)
);

TRACE_EVENT(vmbus_onoffer,
	    TP_PROTO(const struct vmbus_channel_offer_channel *offer),
	    TP_ARGS(offer),
	    TP_STRUCT__entry(
		    __field(u32, child_relid)
		    __field(u8, monitorid)
		    __field(u16, is_ddc_int)
		    __field(u32, connection_id)
		    __array(char, if_type, 16)
		    __array(char, if_instance, 16)
		    __field(u16, chn_flags)
		    __field(u16, mmio_mb)
		    __field(u16, sub_idx)
		    ),
	    TP_fast_assign(__entry->child_relid = offer->child_relid;
			   __entry->monitorid = offer->monitorid;
			   __entry->is_ddc_int = offer->is_dedicated_interrupt;
			   __entry->connection_id = offer->connection_id;
			   memcpy(__entry->if_type,
				  &offer->offer.if_type.b, 16);
			   memcpy(__entry->if_instance,
				  &offer->offer.if_instance.b, 16);
			   __entry->chn_flags = offer->offer.chn_flags;
			   __entry->mmio_mb = offer->offer.mmio_megabytes;
			   __entry->sub_idx = offer->offer.sub_channel_index;
		    ),
	    TP_printk("child_relid 0x%x, monitorid 0x%x, is_dedicated %d, "
		      "connection_id 0x%x, if_type %pUl, if_instance %pUl, "
		      "chn_flags 0x%x, mmio_megabytes %d, sub_channel_index %d",
		      __entry->child_relid, __entry->monitorid,
		      __entry->is_ddc_int, __entry->connection_id,
		      __entry->if_type, __entry->if_instance,
		      __entry->chn_flags, __entry->mmio_mb,
		      __entry->sub_idx
	    )
	);

#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#undef TRACE_INCLUDE_FILE
#define TRACE_INCLUDE_FILE hv_trace
#endif /* _HV_TRACE_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
