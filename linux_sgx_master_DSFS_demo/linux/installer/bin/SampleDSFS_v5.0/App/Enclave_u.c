#include "Enclave_u.h"
#include <errno.h>

typedef struct ms_ecall_type_char_t {
	char ms_val;
} ms_ecall_type_char_t;

typedef struct ms_ecall_type_int_t {
	int ms_val;
} ms_ecall_type_int_t;

typedef struct ms_ecall_type_float_t {
	float ms_val;
} ms_ecall_type_float_t;

typedef struct ms_ecall_type_double_t {
	double ms_val;
} ms_ecall_type_double_t;

typedef struct ms_ecall_type_size_t_t {
	size_t ms_val;
} ms_ecall_type_size_t_t;

typedef struct ms_ecall_type_wchar_t_t {
	wchar_t ms_val;
} ms_ecall_type_wchar_t_t;

typedef struct ms_ecall_type_struct_t {
	struct struct_foo_t ms_val;
} ms_ecall_type_struct_t;

typedef struct ms_ecall_type_enum_union_t {
	enum enum_foo_t ms_val1;
	union union_foo_t* ms_val2;
} ms_ecall_type_enum_union_t;

typedef struct ms_ecall_pointer_user_check_t {
	size_t ms_retval;
	void* ms_val;
	size_t ms_sz;
} ms_ecall_pointer_user_check_t;

typedef struct ms_ecall_pointer_in_t {
	int* ms_val;
} ms_ecall_pointer_in_t;

typedef struct ms_ecall_pointer_out_t {
	int* ms_val;
} ms_ecall_pointer_out_t;

typedef struct ms_ecall_pointer_in_out_t {
	int* ms_val;
} ms_ecall_pointer_in_out_t;

typedef struct ms_ecall_pointer_string_t {
	char* ms_str;
	size_t ms_str_len;
} ms_ecall_pointer_string_t;

typedef struct ms_ecall_pointer_string_const_t {
	char* ms_str;
	size_t ms_str_len;
} ms_ecall_pointer_string_const_t;

typedef struct ms_ecall_pointer_size_t {
	void* ms_ptr;
	size_t ms_len;
} ms_ecall_pointer_size_t;

typedef struct ms_ecall_pointer_count_t {
	int* ms_arr;
	int ms_cnt;
} ms_ecall_pointer_count_t;

typedef struct ms_ecall_pointer_isptr_readonly_t {
	buffer_t ms_buf;
	size_t ms_len;
} ms_ecall_pointer_isptr_readonly_t;

typedef struct ms_ecall_IPFS_function_t {
	char* ms_file_name;
	char* ms_datas;
	size_t ms_cnt_name;
	size_t ms_cnt_datas;
} ms_ecall_IPFS_function_t;

typedef struct ms_ecall_array_user_check_t {
	int* ms_arr;
} ms_ecall_array_user_check_t;

typedef struct ms_ecall_array_in_t {
	int* ms_arr;
} ms_ecall_array_in_t;

typedef struct ms_ecall_array_out_t {
	int* ms_arr;
} ms_ecall_array_out_t;

typedef struct ms_ecall_array_in_out_t {
	int* ms_arr;
} ms_ecall_array_in_out_t;

typedef struct ms_ecall_array_isary_t {
	array_t*  ms_arr;
} ms_ecall_array_isary_t;

typedef struct ms_ecall_function_private_t {
	int ms_retval;
} ms_ecall_function_private_t;

typedef struct ms_ecall_sgx_cpuid_t {
	int* ms_cpuinfo;
	int ms_leaf;
} ms_ecall_sgx_cpuid_t;

typedef struct ms_ecall_increase_counter_t {
	size_t ms_retval;
} ms_ecall_increase_counter_t;

typedef struct ms_ocall_print_string_t {
	char* ms_str;
} ms_ocall_print_string_t;

typedef struct ms_ocall_pointer_user_check_t {
	int* ms_val;
} ms_ocall_pointer_user_check_t;

typedef struct ms_ocall_pointer_in_t {
	int* ms_val;
} ms_ocall_pointer_in_t;

typedef struct ms_ocall_pointer_out_t {
	int* ms_val;
} ms_ocall_pointer_out_t;

typedef struct ms_ocall_pointer_in_out_t {
	int* ms_val;
} ms_ocall_pointer_in_out_t;

typedef struct ms_u_sgxprotectedfs_exclusive_file_open_t {
	void* ms_retval;
	char* ms_filename;
	uint8_t ms_read_only;
	int64_t* ms_file_size;
	int32_t* ms_error_code;
} ms_u_sgxprotectedfs_exclusive_file_open_t;

typedef struct ms_u_sgxprotectedfs_check_if_file_exists_t {
	uint8_t ms_retval;
	char* ms_filename;
} ms_u_sgxprotectedfs_check_if_file_exists_t;

typedef struct ms_u_sgxprotectedfs_fread_node_t {
	int32_t ms_retval;
	void* ms_f;
	uint64_t ms_node_number;
	uint8_t* ms_buffer;
	uint32_t ms_node_size;
} ms_u_sgxprotectedfs_fread_node_t;

typedef struct ms_u_sgxprotectedfs_fwrite_node_t {
	int32_t ms_retval;
	void* ms_f;
	uint64_t ms_node_number;
	uint8_t* ms_buffer;
	uint32_t ms_node_size;
} ms_u_sgxprotectedfs_fwrite_node_t;

typedef struct ms_u_sgxprotectedfs_fwrite_node_ecdsa_t {
	int32_t ms_retval;
	void* ms_f;
	uint64_t ms_node_number;
	uint8_t* ms_buffer;
	uint32_t ms_node_size;
	uint8_t* ms_p_signature;
} ms_u_sgxprotectedfs_fwrite_node_ecdsa_t;

typedef struct ms_u_sgxprotectedfs_fread_node_ecdsa_t {
	int32_t ms_retval;
	void* ms_f;
	uint64_t ms_node_number;
	uint8_t* ms_buffer;
	uint32_t ms_node_size;
	uint8_t* ms_p_signature;
} ms_u_sgxprotectedfs_fread_node_ecdsa_t;

typedef struct ms_u_sgxprotectedfs_fclose_t {
	int32_t ms_retval;
	void* ms_f;
} ms_u_sgxprotectedfs_fclose_t;

typedef struct ms_u_sgxprotectedfs_fflush_t {
	uint8_t ms_retval;
	void* ms_f;
} ms_u_sgxprotectedfs_fflush_t;

typedef struct ms_u_sgxprotectedfs_remove_t {
	int32_t ms_retval;
	char* ms_filename;
} ms_u_sgxprotectedfs_remove_t;

typedef struct ms_u_sgxprotectedfs_recovery_file_open_t {
	void* ms_retval;
	char* ms_filename;
} ms_u_sgxprotectedfs_recovery_file_open_t;

typedef struct ms_u_sgxprotectedfs_fwrite_recovery_node_t {
	uint8_t ms_retval;
	void* ms_f;
	uint8_t* ms_data;
	uint32_t ms_data_length;
} ms_u_sgxprotectedfs_fwrite_recovery_node_t;

typedef struct ms_u_sgxprotectedfs_do_file_recovery_t {
	int32_t ms_retval;
	char* ms_filename;
	char* ms_recovery_filename;
	uint32_t ms_node_size;
} ms_u_sgxprotectedfs_do_file_recovery_t;

typedef struct ms_create_session_ocall_t {
	sgx_status_t ms_retval;
	uint32_t* ms_sid;
	uint8_t* ms_dh_msg1;
	uint32_t ms_dh_msg1_size;
	uint32_t ms_timeout;
} ms_create_session_ocall_t;

typedef struct ms_exchange_report_ocall_t {
	sgx_status_t ms_retval;
	uint32_t ms_sid;
	uint8_t* ms_dh_msg2;
	uint32_t ms_dh_msg2_size;
	uint8_t* ms_dh_msg3;
	uint32_t ms_dh_msg3_size;
	uint32_t ms_timeout;
} ms_exchange_report_ocall_t;

typedef struct ms_close_session_ocall_t {
	sgx_status_t ms_retval;
	uint32_t ms_sid;
	uint32_t ms_timeout;
} ms_close_session_ocall_t;

typedef struct ms_invoke_service_ocall_t {
	sgx_status_t ms_retval;
	uint8_t* ms_pse_message_req;
	uint32_t ms_pse_message_req_size;
	uint8_t* ms_pse_message_resp;
	uint32_t ms_pse_message_resp_size;
	uint32_t ms_timeout;
} ms_invoke_service_ocall_t;

typedef struct ms_sgx_oc_cpuidex_t {
	int* ms_cpuinfo;
	int ms_leaf;
	int ms_subleaf;
} ms_sgx_oc_cpuidex_t;

typedef struct ms_sgx_thread_wait_untrusted_event_ocall_t {
	int ms_retval;
	void* ms_self;
} ms_sgx_thread_wait_untrusted_event_ocall_t;

typedef struct ms_sgx_thread_set_untrusted_event_ocall_t {
	int ms_retval;
	void* ms_waiter;
} ms_sgx_thread_set_untrusted_event_ocall_t;

typedef struct ms_sgx_thread_setwait_untrusted_events_ocall_t {
	int ms_retval;
	void* ms_waiter;
	void* ms_self;
} ms_sgx_thread_setwait_untrusted_events_ocall_t;

typedef struct ms_sgx_thread_set_multiple_untrusted_events_ocall_t {
	int ms_retval;
	void** ms_waiters;
	size_t ms_total;
} ms_sgx_thread_set_multiple_untrusted_events_ocall_t;

typedef struct ms_memccpy_t {
	void* ms_retval;
	void* ms_dest;
	void* ms_src;
	int ms_val;
	size_t ms_len;
} ms_memccpy_t;

static sgx_status_t SGX_CDECL Enclave_ocall_print_string(void* pms)
{
	ms_ocall_print_string_t* ms = SGX_CAST(ms_ocall_print_string_t*, pms);
	ocall_print_string((const char*)ms->ms_str);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_pointer_user_check(void* pms)
{
	ms_ocall_pointer_user_check_t* ms = SGX_CAST(ms_ocall_pointer_user_check_t*, pms);
	ocall_pointer_user_check(ms->ms_val);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_pointer_in(void* pms)
{
	ms_ocall_pointer_in_t* ms = SGX_CAST(ms_ocall_pointer_in_t*, pms);
	ocall_pointer_in(ms->ms_val);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_pointer_out(void* pms)
{
	ms_ocall_pointer_out_t* ms = SGX_CAST(ms_ocall_pointer_out_t*, pms);
	ocall_pointer_out(ms->ms_val);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_pointer_in_out(void* pms)
{
	ms_ocall_pointer_in_out_t* ms = SGX_CAST(ms_ocall_pointer_in_out_t*, pms);
	ocall_pointer_in_out(ms->ms_val);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_u_sgxprotectedfs_exclusive_file_open(void* pms)
{
	ms_u_sgxprotectedfs_exclusive_file_open_t* ms = SGX_CAST(ms_u_sgxprotectedfs_exclusive_file_open_t*, pms);
	ms->ms_retval = u_sgxprotectedfs_exclusive_file_open((const char*)ms->ms_filename, ms->ms_read_only, ms->ms_file_size, ms->ms_error_code);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_u_sgxprotectedfs_check_if_file_exists(void* pms)
{
	ms_u_sgxprotectedfs_check_if_file_exists_t* ms = SGX_CAST(ms_u_sgxprotectedfs_check_if_file_exists_t*, pms);
	ms->ms_retval = u_sgxprotectedfs_check_if_file_exists((const char*)ms->ms_filename);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_u_sgxprotectedfs_fread_node(void* pms)
{
	ms_u_sgxprotectedfs_fread_node_t* ms = SGX_CAST(ms_u_sgxprotectedfs_fread_node_t*, pms);
	ms->ms_retval = u_sgxprotectedfs_fread_node(ms->ms_f, ms->ms_node_number, ms->ms_buffer, ms->ms_node_size);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_u_sgxprotectedfs_fwrite_node(void* pms)
{
	ms_u_sgxprotectedfs_fwrite_node_t* ms = SGX_CAST(ms_u_sgxprotectedfs_fwrite_node_t*, pms);
	ms->ms_retval = u_sgxprotectedfs_fwrite_node(ms->ms_f, ms->ms_node_number, ms->ms_buffer, ms->ms_node_size);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_u_sgxprotectedfs_fwrite_node_ecdsa(void* pms)
{
	ms_u_sgxprotectedfs_fwrite_node_ecdsa_t* ms = SGX_CAST(ms_u_sgxprotectedfs_fwrite_node_ecdsa_t*, pms);
	ms->ms_retval = u_sgxprotectedfs_fwrite_node_ecdsa(ms->ms_f, ms->ms_node_number, ms->ms_buffer, ms->ms_node_size, ms->ms_p_signature);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_u_sgxprotectedfs_fread_node_ecdsa(void* pms)
{
	ms_u_sgxprotectedfs_fread_node_ecdsa_t* ms = SGX_CAST(ms_u_sgxprotectedfs_fread_node_ecdsa_t*, pms);
	ms->ms_retval = u_sgxprotectedfs_fread_node_ecdsa(ms->ms_f, ms->ms_node_number, ms->ms_buffer, ms->ms_node_size, ms->ms_p_signature);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_u_sgxprotectedfs_fclose(void* pms)
{
	ms_u_sgxprotectedfs_fclose_t* ms = SGX_CAST(ms_u_sgxprotectedfs_fclose_t*, pms);
	ms->ms_retval = u_sgxprotectedfs_fclose(ms->ms_f);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_u_sgxprotectedfs_fflush(void* pms)
{
	ms_u_sgxprotectedfs_fflush_t* ms = SGX_CAST(ms_u_sgxprotectedfs_fflush_t*, pms);
	ms->ms_retval = u_sgxprotectedfs_fflush(ms->ms_f);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_u_sgxprotectedfs_remove(void* pms)
{
	ms_u_sgxprotectedfs_remove_t* ms = SGX_CAST(ms_u_sgxprotectedfs_remove_t*, pms);
	ms->ms_retval = u_sgxprotectedfs_remove((const char*)ms->ms_filename);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_u_sgxprotectedfs_recovery_file_open(void* pms)
{
	ms_u_sgxprotectedfs_recovery_file_open_t* ms = SGX_CAST(ms_u_sgxprotectedfs_recovery_file_open_t*, pms);
	ms->ms_retval = u_sgxprotectedfs_recovery_file_open((const char*)ms->ms_filename);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_u_sgxprotectedfs_fwrite_recovery_node(void* pms)
{
	ms_u_sgxprotectedfs_fwrite_recovery_node_t* ms = SGX_CAST(ms_u_sgxprotectedfs_fwrite_recovery_node_t*, pms);
	ms->ms_retval = u_sgxprotectedfs_fwrite_recovery_node(ms->ms_f, ms->ms_data, ms->ms_data_length);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_u_sgxprotectedfs_do_file_recovery(void* pms)
{
	ms_u_sgxprotectedfs_do_file_recovery_t* ms = SGX_CAST(ms_u_sgxprotectedfs_do_file_recovery_t*, pms);
	ms->ms_retval = u_sgxprotectedfs_do_file_recovery((const char*)ms->ms_filename, (const char*)ms->ms_recovery_filename, ms->ms_node_size);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_create_session_ocall(void* pms)
{
	ms_create_session_ocall_t* ms = SGX_CAST(ms_create_session_ocall_t*, pms);
	ms->ms_retval = create_session_ocall(ms->ms_sid, ms->ms_dh_msg1, ms->ms_dh_msg1_size, ms->ms_timeout);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_exchange_report_ocall(void* pms)
{
	ms_exchange_report_ocall_t* ms = SGX_CAST(ms_exchange_report_ocall_t*, pms);
	ms->ms_retval = exchange_report_ocall(ms->ms_sid, ms->ms_dh_msg2, ms->ms_dh_msg2_size, ms->ms_dh_msg3, ms->ms_dh_msg3_size, ms->ms_timeout);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_close_session_ocall(void* pms)
{
	ms_close_session_ocall_t* ms = SGX_CAST(ms_close_session_ocall_t*, pms);
	ms->ms_retval = close_session_ocall(ms->ms_sid, ms->ms_timeout);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_invoke_service_ocall(void* pms)
{
	ms_invoke_service_ocall_t* ms = SGX_CAST(ms_invoke_service_ocall_t*, pms);
	ms->ms_retval = invoke_service_ocall(ms->ms_pse_message_req, ms->ms_pse_message_req_size, ms->ms_pse_message_resp, ms->ms_pse_message_resp_size, ms->ms_timeout);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_sgx_oc_cpuidex(void* pms)
{
	ms_sgx_oc_cpuidex_t* ms = SGX_CAST(ms_sgx_oc_cpuidex_t*, pms);
	sgx_oc_cpuidex(ms->ms_cpuinfo, ms->ms_leaf, ms->ms_subleaf);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_sgx_thread_wait_untrusted_event_ocall(void* pms)
{
	ms_sgx_thread_wait_untrusted_event_ocall_t* ms = SGX_CAST(ms_sgx_thread_wait_untrusted_event_ocall_t*, pms);
	ms->ms_retval = sgx_thread_wait_untrusted_event_ocall((const void*)ms->ms_self);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_sgx_thread_set_untrusted_event_ocall(void* pms)
{
	ms_sgx_thread_set_untrusted_event_ocall_t* ms = SGX_CAST(ms_sgx_thread_set_untrusted_event_ocall_t*, pms);
	ms->ms_retval = sgx_thread_set_untrusted_event_ocall((const void*)ms->ms_waiter);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_sgx_thread_setwait_untrusted_events_ocall(void* pms)
{
	ms_sgx_thread_setwait_untrusted_events_ocall_t* ms = SGX_CAST(ms_sgx_thread_setwait_untrusted_events_ocall_t*, pms);
	ms->ms_retval = sgx_thread_setwait_untrusted_events_ocall((const void*)ms->ms_waiter, (const void*)ms->ms_self);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_sgx_thread_set_multiple_untrusted_events_ocall(void* pms)
{
	ms_sgx_thread_set_multiple_untrusted_events_ocall_t* ms = SGX_CAST(ms_sgx_thread_set_multiple_untrusted_events_ocall_t*, pms);
	ms->ms_retval = sgx_thread_set_multiple_untrusted_events_ocall((const void**)ms->ms_waiters, ms->ms_total);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_memccpy(void* pms)
{
	ms_memccpy_t* ms = SGX_CAST(ms_memccpy_t*, pms);
	ms->ms_retval = memccpy(ms->ms_dest, (const void*)ms->ms_src, ms->ms_val, ms->ms_len);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_function_allow(void* pms)
{
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	ocall_function_allow();
	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * table[28];
} ocall_table_Enclave = {
	28,
	{
		(void*)Enclave_ocall_print_string,
		(void*)Enclave_ocall_pointer_user_check,
		(void*)Enclave_ocall_pointer_in,
		(void*)Enclave_ocall_pointer_out,
		(void*)Enclave_ocall_pointer_in_out,
		(void*)Enclave_u_sgxprotectedfs_exclusive_file_open,
		(void*)Enclave_u_sgxprotectedfs_check_if_file_exists,
		(void*)Enclave_u_sgxprotectedfs_fread_node,
		(void*)Enclave_u_sgxprotectedfs_fwrite_node,
		(void*)Enclave_u_sgxprotectedfs_fwrite_node_ecdsa,
		(void*)Enclave_u_sgxprotectedfs_fread_node_ecdsa,
		(void*)Enclave_u_sgxprotectedfs_fclose,
		(void*)Enclave_u_sgxprotectedfs_fflush,
		(void*)Enclave_u_sgxprotectedfs_remove,
		(void*)Enclave_u_sgxprotectedfs_recovery_file_open,
		(void*)Enclave_u_sgxprotectedfs_fwrite_recovery_node,
		(void*)Enclave_u_sgxprotectedfs_do_file_recovery,
		(void*)Enclave_create_session_ocall,
		(void*)Enclave_exchange_report_ocall,
		(void*)Enclave_close_session_ocall,
		(void*)Enclave_invoke_service_ocall,
		(void*)Enclave_sgx_oc_cpuidex,
		(void*)Enclave_sgx_thread_wait_untrusted_event_ocall,
		(void*)Enclave_sgx_thread_set_untrusted_event_ocall,
		(void*)Enclave_sgx_thread_setwait_untrusted_events_ocall,
		(void*)Enclave_sgx_thread_set_multiple_untrusted_events_ocall,
		(void*)Enclave_memccpy,
		(void*)Enclave_ocall_function_allow,
	}
};
sgx_status_t ecall_type_char(sgx_enclave_id_t eid, char val)
{
	sgx_status_t status;
	ms_ecall_type_char_t ms;
	ms.ms_val = val;
	status = sgx_ecall(eid, 0, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_type_int(sgx_enclave_id_t eid, int val)
{
	sgx_status_t status;
	ms_ecall_type_int_t ms;
	ms.ms_val = val;
	status = sgx_ecall(eid, 1, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_type_float(sgx_enclave_id_t eid, float val)
{
	sgx_status_t status;
	ms_ecall_type_float_t ms;
	ms.ms_val = val;
	status = sgx_ecall(eid, 2, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_type_double(sgx_enclave_id_t eid, double val)
{
	sgx_status_t status;
	ms_ecall_type_double_t ms;
	ms.ms_val = val;
	status = sgx_ecall(eid, 3, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_type_size_t(sgx_enclave_id_t eid, size_t val)
{
	sgx_status_t status;
	ms_ecall_type_size_t_t ms;
	ms.ms_val = val;
	status = sgx_ecall(eid, 4, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_type_wchar_t(sgx_enclave_id_t eid, wchar_t val)
{
	sgx_status_t status;
	ms_ecall_type_wchar_t_t ms;
	ms.ms_val = val;
	status = sgx_ecall(eid, 5, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_type_struct(sgx_enclave_id_t eid, struct struct_foo_t val)
{
	sgx_status_t status;
	ms_ecall_type_struct_t ms;
	ms.ms_val = val;
	status = sgx_ecall(eid, 6, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_type_enum_union(sgx_enclave_id_t eid, enum enum_foo_t val1, union union_foo_t* val2)
{
	sgx_status_t status;
	ms_ecall_type_enum_union_t ms;
	ms.ms_val1 = val1;
	ms.ms_val2 = val2;
	status = sgx_ecall(eid, 7, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_pointer_user_check(sgx_enclave_id_t eid, size_t* retval, void* val, size_t sz)
{
	sgx_status_t status;
	ms_ecall_pointer_user_check_t ms;
	ms.ms_val = val;
	ms.ms_sz = sz;
	status = sgx_ecall(eid, 8, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t ecall_pointer_in(sgx_enclave_id_t eid, int* val)
{
	sgx_status_t status;
	ms_ecall_pointer_in_t ms;
	ms.ms_val = val;
	status = sgx_ecall(eid, 9, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_pointer_out(sgx_enclave_id_t eid, int* val)
{
	sgx_status_t status;
	ms_ecall_pointer_out_t ms;
	ms.ms_val = val;
	status = sgx_ecall(eid, 10, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_pointer_in_out(sgx_enclave_id_t eid, int* val)
{
	sgx_status_t status;
	ms_ecall_pointer_in_out_t ms;
	ms.ms_val = val;
	status = sgx_ecall(eid, 11, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_pointer_string(sgx_enclave_id_t eid, char* str)
{
	sgx_status_t status;
	ms_ecall_pointer_string_t ms;
	ms.ms_str = (char*)str;
	ms.ms_str_len = str ? strlen(str) + 1 : 0;
	status = sgx_ecall(eid, 12, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_pointer_string_const(sgx_enclave_id_t eid, const char* str)
{
	sgx_status_t status;
	ms_ecall_pointer_string_const_t ms;
	ms.ms_str = (char*)str;
	ms.ms_str_len = str ? strlen(str) + 1 : 0;
	status = sgx_ecall(eid, 13, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_pointer_size(sgx_enclave_id_t eid, void* ptr, size_t len)
{
	sgx_status_t status;
	ms_ecall_pointer_size_t ms;
	ms.ms_ptr = ptr;
	ms.ms_len = len;
	status = sgx_ecall(eid, 14, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_pointer_count(sgx_enclave_id_t eid, int* arr, int cnt)
{
	sgx_status_t status;
	ms_ecall_pointer_count_t ms;
	ms.ms_arr = arr;
	ms.ms_cnt = cnt;
	status = sgx_ecall(eid, 15, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_pointer_isptr_readonly(sgx_enclave_id_t eid, buffer_t buf, size_t len)
{
	sgx_status_t status;
	ms_ecall_pointer_isptr_readonly_t ms;
	ms.ms_buf = (buffer_t)buf;
	ms.ms_len = len;
	status = sgx_ecall(eid, 16, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_IPFS_function(sgx_enclave_id_t eid, char* file_name, char* datas, size_t cnt_name, size_t cnt_datas)
{
	sgx_status_t status;
	ms_ecall_IPFS_function_t ms;
	ms.ms_file_name = file_name;
	ms.ms_datas = datas;
	ms.ms_cnt_name = cnt_name;
	ms.ms_cnt_datas = cnt_datas;
	status = sgx_ecall(eid, 17, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ocall_pointer_attr(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 18, &ocall_table_Enclave, NULL);
	return status;
}

sgx_status_t ecall_array_user_check(sgx_enclave_id_t eid, int arr[4])
{
	sgx_status_t status;
	ms_ecall_array_user_check_t ms;
	ms.ms_arr = (int*)arr;
	status = sgx_ecall(eid, 19, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_array_in(sgx_enclave_id_t eid, int arr[4])
{
	sgx_status_t status;
	ms_ecall_array_in_t ms;
	ms.ms_arr = (int*)arr;
	status = sgx_ecall(eid, 20, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_array_out(sgx_enclave_id_t eid, int arr[4])
{
	sgx_status_t status;
	ms_ecall_array_out_t ms;
	ms.ms_arr = (int*)arr;
	status = sgx_ecall(eid, 21, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_array_in_out(sgx_enclave_id_t eid, int arr[4])
{
	sgx_status_t status;
	ms_ecall_array_in_out_t ms;
	ms.ms_arr = (int*)arr;
	status = sgx_ecall(eid, 22, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_array_isary(sgx_enclave_id_t eid, array_t arr)
{
	sgx_status_t status;
	ms_ecall_array_isary_t ms;
	ms.ms_arr = (array_t *)&arr[0];
	status = sgx_ecall(eid, 23, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_function_calling_convs(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 24, &ocall_table_Enclave, NULL);
	return status;
}

sgx_status_t ecall_function_public(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 25, &ocall_table_Enclave, NULL);
	return status;
}

sgx_status_t ecall_function_private(sgx_enclave_id_t eid, int* retval)
{
	sgx_status_t status;
	ms_ecall_function_private_t ms;
	status = sgx_ecall(eid, 26, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t ecall_malloc_free(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 27, &ocall_table_Enclave, NULL);
	return status;
}

sgx_status_t ecall_sgx_cpuid(sgx_enclave_id_t eid, int cpuinfo[4], int leaf)
{
	sgx_status_t status;
	ms_ecall_sgx_cpuid_t ms;
	ms.ms_cpuinfo = (int*)cpuinfo;
	ms.ms_leaf = leaf;
	status = sgx_ecall(eid, 28, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_exception(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 29, &ocall_table_Enclave, NULL);
	return status;
}

sgx_status_t ecall_map(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 30, &ocall_table_Enclave, NULL);
	return status;
}

sgx_status_t ecall_increase_counter(sgx_enclave_id_t eid, size_t* retval)
{
	sgx_status_t status;
	ms_ecall_increase_counter_t ms;
	status = sgx_ecall(eid, 31, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t ecall_producer(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 32, &ocall_table_Enclave, NULL);
	return status;
}

sgx_status_t ecall_consumer(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 33, &ocall_table_Enclave, NULL);
	return status;
}

