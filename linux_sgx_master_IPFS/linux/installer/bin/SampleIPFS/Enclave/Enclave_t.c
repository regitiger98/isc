#include "Enclave_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */
#include "sgx_lfence.h" /* for sgx_lfence */

#include <errno.h>
#include <mbusafecrt.h> /* for memcpy_s etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_ENCLAVE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_within_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)


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
	const char* ms_str;
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
	size_t ms_iter;
	size_t ms_mode;
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
	const char* ms_str;
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
	const char* ms_filename;
	uint8_t ms_read_only;
	int64_t* ms_file_size;
	int32_t* ms_error_code;
} ms_u_sgxprotectedfs_exclusive_file_open_t;

typedef struct ms_u_sgxprotectedfs_check_if_file_exists_t {
	uint8_t ms_retval;
	const char* ms_filename;
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
	const char* ms_filename;
} ms_u_sgxprotectedfs_remove_t;

typedef struct ms_u_sgxprotectedfs_recovery_file_open_t {
	void* ms_retval;
	const char* ms_filename;
} ms_u_sgxprotectedfs_recovery_file_open_t;

typedef struct ms_u_sgxprotectedfs_fwrite_recovery_node_t {
	uint8_t ms_retval;
	void* ms_f;
	uint8_t* ms_data;
	uint32_t ms_data_length;
} ms_u_sgxprotectedfs_fwrite_recovery_node_t;

typedef struct ms_u_sgxprotectedfs_do_file_recovery_t {
	int32_t ms_retval;
	const char* ms_filename;
	const char* ms_recovery_filename;
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
	const void* ms_self;
} ms_sgx_thread_wait_untrusted_event_ocall_t;

typedef struct ms_sgx_thread_set_untrusted_event_ocall_t {
	int ms_retval;
	const void* ms_waiter;
} ms_sgx_thread_set_untrusted_event_ocall_t;

typedef struct ms_sgx_thread_setwait_untrusted_events_ocall_t {
	int ms_retval;
	const void* ms_waiter;
	const void* ms_self;
} ms_sgx_thread_setwait_untrusted_events_ocall_t;

typedef struct ms_sgx_thread_set_multiple_untrusted_events_ocall_t {
	int ms_retval;
	const void** ms_waiters;
	size_t ms_total;
} ms_sgx_thread_set_multiple_untrusted_events_ocall_t;

typedef struct ms_memccpy_t {
	void* ms_retval;
	void* ms_dest;
	const void* ms_src;
	int ms_val;
	size_t ms_len;
} ms_memccpy_t;

static sgx_status_t SGX_CDECL sgx_ecall_type_char(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_type_char_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_type_char_t* ms = SGX_CAST(ms_ecall_type_char_t*, pms);
	sgx_status_t status = SGX_SUCCESS;



	ecall_type_char(ms->ms_val);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_type_int(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_type_int_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_type_int_t* ms = SGX_CAST(ms_ecall_type_int_t*, pms);
	sgx_status_t status = SGX_SUCCESS;



	ecall_type_int(ms->ms_val);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_type_float(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_type_float_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_type_float_t* ms = SGX_CAST(ms_ecall_type_float_t*, pms);
	sgx_status_t status = SGX_SUCCESS;



	ecall_type_float(ms->ms_val);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_type_double(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_type_double_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_type_double_t* ms = SGX_CAST(ms_ecall_type_double_t*, pms);
	sgx_status_t status = SGX_SUCCESS;



	ecall_type_double(ms->ms_val);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_type_size_t(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_type_size_t_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_type_size_t_t* ms = SGX_CAST(ms_ecall_type_size_t_t*, pms);
	sgx_status_t status = SGX_SUCCESS;



	ecall_type_size_t(ms->ms_val);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_type_wchar_t(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_type_wchar_t_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_type_wchar_t_t* ms = SGX_CAST(ms_ecall_type_wchar_t_t*, pms);
	sgx_status_t status = SGX_SUCCESS;



	ecall_type_wchar_t(ms->ms_val);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_type_struct(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_type_struct_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_type_struct_t* ms = SGX_CAST(ms_ecall_type_struct_t*, pms);
	sgx_status_t status = SGX_SUCCESS;



	ecall_type_struct(ms->ms_val);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_type_enum_union(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_type_enum_union_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_type_enum_union_t* ms = SGX_CAST(ms_ecall_type_enum_union_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	union union_foo_t* _tmp_val2 = ms->ms_val2;



	ecall_type_enum_union(ms->ms_val1, _tmp_val2);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_pointer_user_check(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_pointer_user_check_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_pointer_user_check_t* ms = SGX_CAST(ms_ecall_pointer_user_check_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_val = ms->ms_val;



	ms->ms_retval = ecall_pointer_user_check(_tmp_val, ms->ms_sz);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_pointer_in(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_pointer_in_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_pointer_in_t* ms = SGX_CAST(ms_ecall_pointer_in_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_val = ms->ms_val;
	size_t _len_val = sizeof(int);
	int* _in_val = NULL;

	CHECK_UNIQUE_POINTER(_tmp_val, _len_val);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_val != NULL && _len_val != 0) {
		_in_val = (int*)malloc(_len_val);
		if (_in_val == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_val, _len_val, _tmp_val, _len_val)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}

	ecall_pointer_in(_in_val);
err:
	if (_in_val) free(_in_val);

	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_pointer_out(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_pointer_out_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_pointer_out_t* ms = SGX_CAST(ms_ecall_pointer_out_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_val = ms->ms_val;
	size_t _len_val = sizeof(int);
	int* _in_val = NULL;

	CHECK_UNIQUE_POINTER(_tmp_val, _len_val);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_val != NULL && _len_val != 0) {
		if ((_in_val = (int*)malloc(_len_val)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_val, 0, _len_val);
	}

	ecall_pointer_out(_in_val);
err:
	if (_in_val) {
		if (memcpy_s(_tmp_val, _len_val, _in_val, _len_val)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_val);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_pointer_in_out(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_pointer_in_out_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_pointer_in_out_t* ms = SGX_CAST(ms_ecall_pointer_in_out_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_val = ms->ms_val;
	size_t _len_val = sizeof(int);
	int* _in_val = NULL;

	CHECK_UNIQUE_POINTER(_tmp_val, _len_val);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_val != NULL && _len_val != 0) {
		_in_val = (int*)malloc(_len_val);
		if (_in_val == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_val, _len_val, _tmp_val, _len_val)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}

	ecall_pointer_in_out(_in_val);
err:
	if (_in_val) {
		if (memcpy_s(_tmp_val, _len_val, _in_val, _len_val)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_val);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_pointer_string(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_pointer_string_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_pointer_string_t* ms = SGX_CAST(ms_ecall_pointer_string_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_str = ms->ms_str;
	size_t _len_str = ms->ms_str_len ;
	char* _in_str = NULL;

	CHECK_UNIQUE_POINTER(_tmp_str, _len_str);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_str != NULL && _len_str != 0) {
		_in_str = (char*)malloc(_len_str);
		if (_in_str == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_str, _len_str, _tmp_str, _len_str)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

		_in_str[_len_str - 1] = '\0';
		if (_len_str != strlen(_in_str) + 1)
		{
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}
	}

	ecall_pointer_string(_in_str);
err:
	if (_in_str)
	{
		_in_str[_len_str - 1] = '\0';
		_len_str = strlen(_in_str) + 1;
		if (memcpy_s((void*)_tmp_str, _len_str, _in_str, _len_str)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_str);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_pointer_string_const(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_pointer_string_const_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_pointer_string_const_t* ms = SGX_CAST(ms_ecall_pointer_string_const_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	const char* _tmp_str = ms->ms_str;
	size_t _len_str = ms->ms_str_len ;
	char* _in_str = NULL;

	CHECK_UNIQUE_POINTER(_tmp_str, _len_str);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_str != NULL && _len_str != 0) {
		_in_str = (char*)malloc(_len_str);
		if (_in_str == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s((void*)_in_str, _len_str, _tmp_str, _len_str)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

		_in_str[_len_str - 1] = '\0';
		if (_len_str != strlen(_in_str) + 1)
		{
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}
	}

	ecall_pointer_string_const((const char*)_in_str);
err:
	if (_in_str) free((void*)_in_str);

	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_pointer_size(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_pointer_size_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_pointer_size_t* ms = SGX_CAST(ms_ecall_pointer_size_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_ptr = ms->ms_ptr;
	size_t _tmp_len = ms->ms_len;
	size_t _len_ptr = _tmp_len;
	void* _in_ptr = NULL;

	CHECK_UNIQUE_POINTER(_tmp_ptr, _len_ptr);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_ptr != NULL && _len_ptr != 0) {
		_in_ptr = (void*)malloc(_len_ptr);
		if (_in_ptr == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_ptr, _len_ptr, _tmp_ptr, _len_ptr)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}

	ecall_pointer_size(_in_ptr, _tmp_len);
err:
	if (_in_ptr) {
		if (memcpy_s(_tmp_ptr, _len_ptr, _in_ptr, _len_ptr)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_ptr);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_pointer_count(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_pointer_count_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_pointer_count_t* ms = SGX_CAST(ms_ecall_pointer_count_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_arr = ms->ms_arr;
	int _tmp_cnt = ms->ms_cnt;
	size_t _len_arr = _tmp_cnt * sizeof(int);
	int* _in_arr = NULL;

	if (sizeof(*_tmp_arr) != 0 &&
		(size_t)_tmp_cnt > (SIZE_MAX / sizeof(*_tmp_arr))) {
		return SGX_ERROR_INVALID_PARAMETER;
	}

	CHECK_UNIQUE_POINTER(_tmp_arr, _len_arr);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_arr != NULL && _len_arr != 0) {
		_in_arr = (int*)malloc(_len_arr);
		if (_in_arr == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_arr, _len_arr, _tmp_arr, _len_arr)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}

	ecall_pointer_count(_in_arr, _tmp_cnt);
err:
	if (_in_arr) {
		if (memcpy_s(_tmp_arr, _len_arr, _in_arr, _len_arr)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_arr);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_pointer_isptr_readonly(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_pointer_isptr_readonly_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_pointer_isptr_readonly_t* ms = SGX_CAST(ms_ecall_pointer_isptr_readonly_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	buffer_t _tmp_buf = ms->ms_buf;
	size_t _tmp_len = ms->ms_len;
	size_t _len_buf = _tmp_len;
	buffer_t _in_buf = NULL;

	CHECK_UNIQUE_POINTER(_tmp_buf, _len_buf);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_buf != NULL && _len_buf != 0) {
		_in_buf = (buffer_t)malloc(_len_buf);
		if (_in_buf == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s((void*)_in_buf, _len_buf, _tmp_buf, _len_buf)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}

	ecall_pointer_isptr_readonly(_in_buf, _tmp_len);
err:
	if (_in_buf) free((void*)_in_buf);

	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_IPFS_function(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_IPFS_function_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_IPFS_function_t* ms = SGX_CAST(ms_ecall_IPFS_function_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_file_name = ms->ms_file_name;
	size_t _len_file_name = 50 * sizeof(char);
	char* _in_file_name = NULL;
	char* _tmp_datas = ms->ms_datas;
	size_t _tmp_cnt_datas = ms->ms_cnt_datas;
	size_t _len_datas = _tmp_cnt_datas * sizeof(char);
	char* _in_datas = NULL;

	if (sizeof(*_tmp_file_name) != 0 &&
		50 > (SIZE_MAX / sizeof(*_tmp_file_name))) {
		return SGX_ERROR_INVALID_PARAMETER;
	}

	if (sizeof(*_tmp_datas) != 0 &&
		(size_t)_tmp_cnt_datas > (SIZE_MAX / sizeof(*_tmp_datas))) {
		return SGX_ERROR_INVALID_PARAMETER;
	}

	CHECK_UNIQUE_POINTER(_tmp_file_name, _len_file_name);
	CHECK_UNIQUE_POINTER(_tmp_datas, _len_datas);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_file_name != NULL && _len_file_name != 0) {
		_in_file_name = (char*)malloc(_len_file_name);
		if (_in_file_name == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_file_name, _len_file_name, _tmp_file_name, _len_file_name)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}
	if (_tmp_datas != NULL && _len_datas != 0) {
		_in_datas = (char*)malloc(_len_datas);
		if (_in_datas == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_datas, _len_datas, _tmp_datas, _len_datas)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}

	ecall_IPFS_function(_in_file_name, _in_datas, ms->ms_iter, ms->ms_mode, _tmp_cnt_datas);
err:
	if (_in_file_name) free(_in_file_name);
	if (_in_datas) free(_in_datas);

	return status;
}

static sgx_status_t SGX_CDECL sgx_ocall_pointer_attr(void* pms)
{
	sgx_status_t status = SGX_SUCCESS;
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	ocall_pointer_attr();
	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_array_user_check(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_array_user_check_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_array_user_check_t* ms = SGX_CAST(ms_ecall_array_user_check_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_arr = ms->ms_arr;



	ecall_array_user_check(_tmp_arr);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_array_in(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_array_in_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_array_in_t* ms = SGX_CAST(ms_ecall_array_in_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_arr = ms->ms_arr;
	size_t _len_arr = 4 * sizeof(int);
	int* _in_arr = NULL;

	CHECK_UNIQUE_POINTER(_tmp_arr, _len_arr);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_arr != NULL && _len_arr != 0) {
		_in_arr = (int*)malloc(_len_arr);
		if (_in_arr == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_arr, _len_arr, _tmp_arr, _len_arr)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}

	ecall_array_in(_in_arr);
err:
	if (_in_arr) free(_in_arr);

	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_array_out(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_array_out_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_array_out_t* ms = SGX_CAST(ms_ecall_array_out_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_arr = ms->ms_arr;
	size_t _len_arr = 4 * sizeof(int);
	int* _in_arr = NULL;

	CHECK_UNIQUE_POINTER(_tmp_arr, _len_arr);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_arr != NULL && _len_arr != 0) {
		if ((_in_arr = (int*)malloc(_len_arr)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_arr, 0, _len_arr);
	}

	ecall_array_out(_in_arr);
err:
	if (_in_arr) {
		if (memcpy_s(_tmp_arr, _len_arr, _in_arr, _len_arr)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_arr);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_array_in_out(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_array_in_out_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_array_in_out_t* ms = SGX_CAST(ms_ecall_array_in_out_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_arr = ms->ms_arr;
	size_t _len_arr = 4 * sizeof(int);
	int* _in_arr = NULL;

	CHECK_UNIQUE_POINTER(_tmp_arr, _len_arr);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_arr != NULL && _len_arr != 0) {
		_in_arr = (int*)malloc(_len_arr);
		if (_in_arr == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_arr, _len_arr, _tmp_arr, _len_arr)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}

	ecall_array_in_out(_in_arr);
err:
	if (_in_arr) {
		if (memcpy_s(_tmp_arr, _len_arr, _in_arr, _len_arr)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_arr);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_array_isary(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_array_isary_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_array_isary_t* ms = SGX_CAST(ms_ecall_array_isary_t*, pms);
	sgx_status_t status = SGX_SUCCESS;



	ecall_array_isary((ms->ms_arr != NULL) ? (*ms->ms_arr) : NULL);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_function_calling_convs(void* pms)
{
	sgx_status_t status = SGX_SUCCESS;
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	ecall_function_calling_convs();
	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_function_public(void* pms)
{
	sgx_status_t status = SGX_SUCCESS;
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	ecall_function_public();
	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_function_private(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_function_private_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_function_private_t* ms = SGX_CAST(ms_ecall_function_private_t*, pms);
	sgx_status_t status = SGX_SUCCESS;



	ms->ms_retval = ecall_function_private();


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_malloc_free(void* pms)
{
	sgx_status_t status = SGX_SUCCESS;
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	ecall_malloc_free();
	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_sgx_cpuid(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_sgx_cpuid_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_sgx_cpuid_t* ms = SGX_CAST(ms_ecall_sgx_cpuid_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_cpuinfo = ms->ms_cpuinfo;
	size_t _len_cpuinfo = 4 * sizeof(int);
	int* _in_cpuinfo = NULL;

	CHECK_UNIQUE_POINTER(_tmp_cpuinfo, _len_cpuinfo);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_cpuinfo != NULL && _len_cpuinfo != 0) {
		if ((_in_cpuinfo = (int*)malloc(_len_cpuinfo)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_cpuinfo, 0, _len_cpuinfo);
	}

	ecall_sgx_cpuid(_in_cpuinfo, ms->ms_leaf);
err:
	if (_in_cpuinfo) {
		if (memcpy_s(_tmp_cpuinfo, _len_cpuinfo, _in_cpuinfo, _len_cpuinfo)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_cpuinfo);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_exception(void* pms)
{
	sgx_status_t status = SGX_SUCCESS;
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	ecall_exception();
	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_map(void* pms)
{
	sgx_status_t status = SGX_SUCCESS;
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	ecall_map();
	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_increase_counter(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_increase_counter_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_increase_counter_t* ms = SGX_CAST(ms_ecall_increase_counter_t*, pms);
	sgx_status_t status = SGX_SUCCESS;



	ms->ms_retval = ecall_increase_counter();


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_producer(void* pms)
{
	sgx_status_t status = SGX_SUCCESS;
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	ecall_producer();
	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_consumer(void* pms)
{
	sgx_status_t status = SGX_SUCCESS;
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	ecall_consumer();
	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* ecall_addr; uint8_t is_priv;} ecall_table[34];
} g_ecall_table = {
	34,
	{
		{(void*)(uintptr_t)sgx_ecall_type_char, 0},
		{(void*)(uintptr_t)sgx_ecall_type_int, 0},
		{(void*)(uintptr_t)sgx_ecall_type_float, 0},
		{(void*)(uintptr_t)sgx_ecall_type_double, 0},
		{(void*)(uintptr_t)sgx_ecall_type_size_t, 0},
		{(void*)(uintptr_t)sgx_ecall_type_wchar_t, 0},
		{(void*)(uintptr_t)sgx_ecall_type_struct, 0},
		{(void*)(uintptr_t)sgx_ecall_type_enum_union, 0},
		{(void*)(uintptr_t)sgx_ecall_pointer_user_check, 0},
		{(void*)(uintptr_t)sgx_ecall_pointer_in, 0},
		{(void*)(uintptr_t)sgx_ecall_pointer_out, 0},
		{(void*)(uintptr_t)sgx_ecall_pointer_in_out, 0},
		{(void*)(uintptr_t)sgx_ecall_pointer_string, 0},
		{(void*)(uintptr_t)sgx_ecall_pointer_string_const, 0},
		{(void*)(uintptr_t)sgx_ecall_pointer_size, 0},
		{(void*)(uintptr_t)sgx_ecall_pointer_count, 0},
		{(void*)(uintptr_t)sgx_ecall_pointer_isptr_readonly, 0},
		{(void*)(uintptr_t)sgx_ecall_IPFS_function, 0},
		{(void*)(uintptr_t)sgx_ocall_pointer_attr, 0},
		{(void*)(uintptr_t)sgx_ecall_array_user_check, 0},
		{(void*)(uintptr_t)sgx_ecall_array_in, 0},
		{(void*)(uintptr_t)sgx_ecall_array_out, 0},
		{(void*)(uintptr_t)sgx_ecall_array_in_out, 0},
		{(void*)(uintptr_t)sgx_ecall_array_isary, 0},
		{(void*)(uintptr_t)sgx_ecall_function_calling_convs, 0},
		{(void*)(uintptr_t)sgx_ecall_function_public, 0},
		{(void*)(uintptr_t)sgx_ecall_function_private, 1},
		{(void*)(uintptr_t)sgx_ecall_malloc_free, 0},
		{(void*)(uintptr_t)sgx_ecall_sgx_cpuid, 0},
		{(void*)(uintptr_t)sgx_ecall_exception, 0},
		{(void*)(uintptr_t)sgx_ecall_map, 0},
		{(void*)(uintptr_t)sgx_ecall_increase_counter, 0},
		{(void*)(uintptr_t)sgx_ecall_producer, 0},
		{(void*)(uintptr_t)sgx_ecall_consumer, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[26][34];
} g_dyn_entry_table = {
	26,
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, },
	}
};


sgx_status_t SGX_CDECL ocall_print_string(const char* str)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_str = str ? strlen(str) + 1 : 0;

	ms_ocall_print_string_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_print_string_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(str, _len_str);

	ocalloc_size += (str != NULL) ? _len_str : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_print_string_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_print_string_t));
	ocalloc_size -= sizeof(ms_ocall_print_string_t);

	if (str != NULL) {
		ms->ms_str = (const char*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, str, _len_str)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_str);
		ocalloc_size -= _len_str;
	} else {
		ms->ms_str = NULL;
	}
	
	status = sgx_ocall(0, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_pointer_user_check(int* val)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_pointer_user_check_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_pointer_user_check_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_pointer_user_check_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_pointer_user_check_t));
	ocalloc_size -= sizeof(ms_ocall_pointer_user_check_t);

	ms->ms_val = val;
	status = sgx_ocall(1, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_pointer_in(int* val)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_val = sizeof(int);

	ms_ocall_pointer_in_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_pointer_in_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(val, _len_val);

	ocalloc_size += (val != NULL) ? _len_val : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_pointer_in_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_pointer_in_t));
	ocalloc_size -= sizeof(ms_ocall_pointer_in_t);

	if (val != NULL) {
		ms->ms_val = (int*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, val, _len_val)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_val);
		ocalloc_size -= _len_val;
	} else {
		ms->ms_val = NULL;
	}
	
	status = sgx_ocall(2, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_pointer_out(int* val)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_val = sizeof(int);

	ms_ocall_pointer_out_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_pointer_out_t);
	void *__tmp = NULL;

	void *__tmp_val = NULL;

	CHECK_ENCLAVE_POINTER(val, _len_val);

	ocalloc_size += (val != NULL) ? _len_val : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_pointer_out_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_pointer_out_t));
	ocalloc_size -= sizeof(ms_ocall_pointer_out_t);

	if (val != NULL) {
		ms->ms_val = (int*)__tmp;
		__tmp_val = __tmp;
		memset(__tmp_val, 0, _len_val);
		__tmp = (void *)((size_t)__tmp + _len_val);
		ocalloc_size -= _len_val;
	} else {
		ms->ms_val = NULL;
	}
	
	status = sgx_ocall(3, ms);

	if (status == SGX_SUCCESS) {
		if (val) {
			if (memcpy_s((void*)val, _len_val, __tmp_val, _len_val)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_pointer_in_out(int* val)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_val = sizeof(int);

	ms_ocall_pointer_in_out_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_pointer_in_out_t);
	void *__tmp = NULL;

	void *__tmp_val = NULL;

	CHECK_ENCLAVE_POINTER(val, _len_val);

	ocalloc_size += (val != NULL) ? _len_val : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_pointer_in_out_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_pointer_in_out_t));
	ocalloc_size -= sizeof(ms_ocall_pointer_in_out_t);

	if (val != NULL) {
		ms->ms_val = (int*)__tmp;
		__tmp_val = __tmp;
		if (memcpy_s(__tmp_val, ocalloc_size, val, _len_val)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_val);
		ocalloc_size -= _len_val;
	} else {
		ms->ms_val = NULL;
	}
	
	status = sgx_ocall(4, ms);

	if (status == SGX_SUCCESS) {
		if (val) {
			if (memcpy_s((void*)val, _len_val, __tmp_val, _len_val)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL u_sgxprotectedfs_exclusive_file_open(void** retval, const char* filename, uint8_t read_only, int64_t* file_size, int32_t* error_code)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_filename = filename ? strlen(filename) + 1 : 0;
	size_t _len_file_size = sizeof(int64_t);
	size_t _len_error_code = sizeof(int32_t);

	ms_u_sgxprotectedfs_exclusive_file_open_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_u_sgxprotectedfs_exclusive_file_open_t);
	void *__tmp = NULL;

	void *__tmp_file_size = NULL;
	void *__tmp_error_code = NULL;

	CHECK_ENCLAVE_POINTER(filename, _len_filename);
	CHECK_ENCLAVE_POINTER(file_size, _len_file_size);
	CHECK_ENCLAVE_POINTER(error_code, _len_error_code);

	ocalloc_size += (filename != NULL) ? _len_filename : 0;
	ocalloc_size += (file_size != NULL) ? _len_file_size : 0;
	ocalloc_size += (error_code != NULL) ? _len_error_code : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_u_sgxprotectedfs_exclusive_file_open_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_u_sgxprotectedfs_exclusive_file_open_t));
	ocalloc_size -= sizeof(ms_u_sgxprotectedfs_exclusive_file_open_t);

	if (filename != NULL) {
		ms->ms_filename = (const char*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, filename, _len_filename)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_filename);
		ocalloc_size -= _len_filename;
	} else {
		ms->ms_filename = NULL;
	}
	
	ms->ms_read_only = read_only;
	if (file_size != NULL) {
		ms->ms_file_size = (int64_t*)__tmp;
		__tmp_file_size = __tmp;
		memset(__tmp_file_size, 0, _len_file_size);
		__tmp = (void *)((size_t)__tmp + _len_file_size);
		ocalloc_size -= _len_file_size;
	} else {
		ms->ms_file_size = NULL;
	}
	
	if (error_code != NULL) {
		ms->ms_error_code = (int32_t*)__tmp;
		__tmp_error_code = __tmp;
		memset(__tmp_error_code, 0, _len_error_code);
		__tmp = (void *)((size_t)__tmp + _len_error_code);
		ocalloc_size -= _len_error_code;
	} else {
		ms->ms_error_code = NULL;
	}
	
	status = sgx_ocall(5, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (file_size) {
			if (memcpy_s((void*)file_size, _len_file_size, __tmp_file_size, _len_file_size)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
		if (error_code) {
			if (memcpy_s((void*)error_code, _len_error_code, __tmp_error_code, _len_error_code)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL u_sgxprotectedfs_check_if_file_exists(uint8_t* retval, const char* filename)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_filename = filename ? strlen(filename) + 1 : 0;

	ms_u_sgxprotectedfs_check_if_file_exists_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_u_sgxprotectedfs_check_if_file_exists_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(filename, _len_filename);

	ocalloc_size += (filename != NULL) ? _len_filename : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_u_sgxprotectedfs_check_if_file_exists_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_u_sgxprotectedfs_check_if_file_exists_t));
	ocalloc_size -= sizeof(ms_u_sgxprotectedfs_check_if_file_exists_t);

	if (filename != NULL) {
		ms->ms_filename = (const char*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, filename, _len_filename)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_filename);
		ocalloc_size -= _len_filename;
	} else {
		ms->ms_filename = NULL;
	}
	
	status = sgx_ocall(6, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL u_sgxprotectedfs_fread_node(int32_t* retval, void* f, uint64_t node_number, uint8_t* buffer, uint32_t node_size)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_buffer = node_size;

	ms_u_sgxprotectedfs_fread_node_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_u_sgxprotectedfs_fread_node_t);
	void *__tmp = NULL;

	void *__tmp_buffer = NULL;

	CHECK_ENCLAVE_POINTER(buffer, _len_buffer);

	ocalloc_size += (buffer != NULL) ? _len_buffer : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_u_sgxprotectedfs_fread_node_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_u_sgxprotectedfs_fread_node_t));
	ocalloc_size -= sizeof(ms_u_sgxprotectedfs_fread_node_t);

	ms->ms_f = f;
	ms->ms_node_number = node_number;
	if (buffer != NULL) {
		ms->ms_buffer = (uint8_t*)__tmp;
		__tmp_buffer = __tmp;
		memset(__tmp_buffer, 0, _len_buffer);
		__tmp = (void *)((size_t)__tmp + _len_buffer);
		ocalloc_size -= _len_buffer;
	} else {
		ms->ms_buffer = NULL;
	}
	
	ms->ms_node_size = node_size;
	status = sgx_ocall(7, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (buffer) {
			if (memcpy_s((void*)buffer, _len_buffer, __tmp_buffer, _len_buffer)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL u_sgxprotectedfs_fwrite_node(int32_t* retval, void* f, uint64_t node_number, uint8_t* buffer, uint32_t node_size)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_buffer = node_size;

	ms_u_sgxprotectedfs_fwrite_node_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_u_sgxprotectedfs_fwrite_node_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(buffer, _len_buffer);

	ocalloc_size += (buffer != NULL) ? _len_buffer : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_u_sgxprotectedfs_fwrite_node_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_u_sgxprotectedfs_fwrite_node_t));
	ocalloc_size -= sizeof(ms_u_sgxprotectedfs_fwrite_node_t);

	ms->ms_f = f;
	ms->ms_node_number = node_number;
	if (buffer != NULL) {
		ms->ms_buffer = (uint8_t*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, buffer, _len_buffer)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_buffer);
		ocalloc_size -= _len_buffer;
	} else {
		ms->ms_buffer = NULL;
	}
	
	ms->ms_node_size = node_size;
	status = sgx_ocall(8, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL u_sgxprotectedfs_fclose(int32_t* retval, void* f)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_u_sgxprotectedfs_fclose_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_u_sgxprotectedfs_fclose_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_u_sgxprotectedfs_fclose_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_u_sgxprotectedfs_fclose_t));
	ocalloc_size -= sizeof(ms_u_sgxprotectedfs_fclose_t);

	ms->ms_f = f;
	status = sgx_ocall(9, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL u_sgxprotectedfs_fflush(uint8_t* retval, void* f)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_u_sgxprotectedfs_fflush_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_u_sgxprotectedfs_fflush_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_u_sgxprotectedfs_fflush_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_u_sgxprotectedfs_fflush_t));
	ocalloc_size -= sizeof(ms_u_sgxprotectedfs_fflush_t);

	ms->ms_f = f;
	status = sgx_ocall(10, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL u_sgxprotectedfs_remove(int32_t* retval, const char* filename)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_filename = filename ? strlen(filename) + 1 : 0;

	ms_u_sgxprotectedfs_remove_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_u_sgxprotectedfs_remove_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(filename, _len_filename);

	ocalloc_size += (filename != NULL) ? _len_filename : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_u_sgxprotectedfs_remove_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_u_sgxprotectedfs_remove_t));
	ocalloc_size -= sizeof(ms_u_sgxprotectedfs_remove_t);

	if (filename != NULL) {
		ms->ms_filename = (const char*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, filename, _len_filename)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_filename);
		ocalloc_size -= _len_filename;
	} else {
		ms->ms_filename = NULL;
	}
	
	status = sgx_ocall(11, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL u_sgxprotectedfs_recovery_file_open(void** retval, const char* filename)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_filename = filename ? strlen(filename) + 1 : 0;

	ms_u_sgxprotectedfs_recovery_file_open_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_u_sgxprotectedfs_recovery_file_open_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(filename, _len_filename);

	ocalloc_size += (filename != NULL) ? _len_filename : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_u_sgxprotectedfs_recovery_file_open_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_u_sgxprotectedfs_recovery_file_open_t));
	ocalloc_size -= sizeof(ms_u_sgxprotectedfs_recovery_file_open_t);

	if (filename != NULL) {
		ms->ms_filename = (const char*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, filename, _len_filename)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_filename);
		ocalloc_size -= _len_filename;
	} else {
		ms->ms_filename = NULL;
	}
	
	status = sgx_ocall(12, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL u_sgxprotectedfs_fwrite_recovery_node(uint8_t* retval, void* f, uint8_t* data, uint32_t data_length)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_data = data_length * sizeof(uint8_t);

	ms_u_sgxprotectedfs_fwrite_recovery_node_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_u_sgxprotectedfs_fwrite_recovery_node_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(data, _len_data);

	ocalloc_size += (data != NULL) ? _len_data : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_u_sgxprotectedfs_fwrite_recovery_node_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_u_sgxprotectedfs_fwrite_recovery_node_t));
	ocalloc_size -= sizeof(ms_u_sgxprotectedfs_fwrite_recovery_node_t);

	ms->ms_f = f;
	if (data != NULL) {
		ms->ms_data = (uint8_t*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, data, _len_data)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_data);
		ocalloc_size -= _len_data;
	} else {
		ms->ms_data = NULL;
	}
	
	ms->ms_data_length = data_length;
	status = sgx_ocall(13, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL u_sgxprotectedfs_do_file_recovery(int32_t* retval, const char* filename, const char* recovery_filename, uint32_t node_size)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_filename = filename ? strlen(filename) + 1 : 0;
	size_t _len_recovery_filename = recovery_filename ? strlen(recovery_filename) + 1 : 0;

	ms_u_sgxprotectedfs_do_file_recovery_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_u_sgxprotectedfs_do_file_recovery_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(filename, _len_filename);
	CHECK_ENCLAVE_POINTER(recovery_filename, _len_recovery_filename);

	ocalloc_size += (filename != NULL) ? _len_filename : 0;
	ocalloc_size += (recovery_filename != NULL) ? _len_recovery_filename : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_u_sgxprotectedfs_do_file_recovery_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_u_sgxprotectedfs_do_file_recovery_t));
	ocalloc_size -= sizeof(ms_u_sgxprotectedfs_do_file_recovery_t);

	if (filename != NULL) {
		ms->ms_filename = (const char*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, filename, _len_filename)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_filename);
		ocalloc_size -= _len_filename;
	} else {
		ms->ms_filename = NULL;
	}
	
	if (recovery_filename != NULL) {
		ms->ms_recovery_filename = (const char*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, recovery_filename, _len_recovery_filename)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_recovery_filename);
		ocalloc_size -= _len_recovery_filename;
	} else {
		ms->ms_recovery_filename = NULL;
	}
	
	ms->ms_node_size = node_size;
	status = sgx_ocall(14, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL create_session_ocall(sgx_status_t* retval, uint32_t* sid, uint8_t* dh_msg1, uint32_t dh_msg1_size, uint32_t timeout)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_sid = sizeof(uint32_t);
	size_t _len_dh_msg1 = dh_msg1_size;

	ms_create_session_ocall_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_create_session_ocall_t);
	void *__tmp = NULL;

	void *__tmp_sid = NULL;
	void *__tmp_dh_msg1 = NULL;

	CHECK_ENCLAVE_POINTER(sid, _len_sid);
	CHECK_ENCLAVE_POINTER(dh_msg1, _len_dh_msg1);

	ocalloc_size += (sid != NULL) ? _len_sid : 0;
	ocalloc_size += (dh_msg1 != NULL) ? _len_dh_msg1 : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_create_session_ocall_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_create_session_ocall_t));
	ocalloc_size -= sizeof(ms_create_session_ocall_t);

	if (sid != NULL) {
		ms->ms_sid = (uint32_t*)__tmp;
		__tmp_sid = __tmp;
		memset(__tmp_sid, 0, _len_sid);
		__tmp = (void *)((size_t)__tmp + _len_sid);
		ocalloc_size -= _len_sid;
	} else {
		ms->ms_sid = NULL;
	}
	
	if (dh_msg1 != NULL) {
		ms->ms_dh_msg1 = (uint8_t*)__tmp;
		__tmp_dh_msg1 = __tmp;
		memset(__tmp_dh_msg1, 0, _len_dh_msg1);
		__tmp = (void *)((size_t)__tmp + _len_dh_msg1);
		ocalloc_size -= _len_dh_msg1;
	} else {
		ms->ms_dh_msg1 = NULL;
	}
	
	ms->ms_dh_msg1_size = dh_msg1_size;
	ms->ms_timeout = timeout;
	status = sgx_ocall(15, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (sid) {
			if (memcpy_s((void*)sid, _len_sid, __tmp_sid, _len_sid)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
		if (dh_msg1) {
			if (memcpy_s((void*)dh_msg1, _len_dh_msg1, __tmp_dh_msg1, _len_dh_msg1)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL exchange_report_ocall(sgx_status_t* retval, uint32_t sid, uint8_t* dh_msg2, uint32_t dh_msg2_size, uint8_t* dh_msg3, uint32_t dh_msg3_size, uint32_t timeout)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_dh_msg2 = dh_msg2_size;
	size_t _len_dh_msg3 = dh_msg3_size;

	ms_exchange_report_ocall_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_exchange_report_ocall_t);
	void *__tmp = NULL;

	void *__tmp_dh_msg3 = NULL;

	CHECK_ENCLAVE_POINTER(dh_msg2, _len_dh_msg2);
	CHECK_ENCLAVE_POINTER(dh_msg3, _len_dh_msg3);

	ocalloc_size += (dh_msg2 != NULL) ? _len_dh_msg2 : 0;
	ocalloc_size += (dh_msg3 != NULL) ? _len_dh_msg3 : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_exchange_report_ocall_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_exchange_report_ocall_t));
	ocalloc_size -= sizeof(ms_exchange_report_ocall_t);

	ms->ms_sid = sid;
	if (dh_msg2 != NULL) {
		ms->ms_dh_msg2 = (uint8_t*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, dh_msg2, _len_dh_msg2)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_dh_msg2);
		ocalloc_size -= _len_dh_msg2;
	} else {
		ms->ms_dh_msg2 = NULL;
	}
	
	ms->ms_dh_msg2_size = dh_msg2_size;
	if (dh_msg3 != NULL) {
		ms->ms_dh_msg3 = (uint8_t*)__tmp;
		__tmp_dh_msg3 = __tmp;
		memset(__tmp_dh_msg3, 0, _len_dh_msg3);
		__tmp = (void *)((size_t)__tmp + _len_dh_msg3);
		ocalloc_size -= _len_dh_msg3;
	} else {
		ms->ms_dh_msg3 = NULL;
	}
	
	ms->ms_dh_msg3_size = dh_msg3_size;
	ms->ms_timeout = timeout;
	status = sgx_ocall(16, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (dh_msg3) {
			if (memcpy_s((void*)dh_msg3, _len_dh_msg3, __tmp_dh_msg3, _len_dh_msg3)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL close_session_ocall(sgx_status_t* retval, uint32_t sid, uint32_t timeout)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_close_session_ocall_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_close_session_ocall_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_close_session_ocall_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_close_session_ocall_t));
	ocalloc_size -= sizeof(ms_close_session_ocall_t);

	ms->ms_sid = sid;
	ms->ms_timeout = timeout;
	status = sgx_ocall(17, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL invoke_service_ocall(sgx_status_t* retval, uint8_t* pse_message_req, uint32_t pse_message_req_size, uint8_t* pse_message_resp, uint32_t pse_message_resp_size, uint32_t timeout)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pse_message_req = pse_message_req_size;
	size_t _len_pse_message_resp = pse_message_resp_size;

	ms_invoke_service_ocall_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_invoke_service_ocall_t);
	void *__tmp = NULL;

	void *__tmp_pse_message_resp = NULL;

	CHECK_ENCLAVE_POINTER(pse_message_req, _len_pse_message_req);
	CHECK_ENCLAVE_POINTER(pse_message_resp, _len_pse_message_resp);

	ocalloc_size += (pse_message_req != NULL) ? _len_pse_message_req : 0;
	ocalloc_size += (pse_message_resp != NULL) ? _len_pse_message_resp : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_invoke_service_ocall_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_invoke_service_ocall_t));
	ocalloc_size -= sizeof(ms_invoke_service_ocall_t);

	if (pse_message_req != NULL) {
		ms->ms_pse_message_req = (uint8_t*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, pse_message_req, _len_pse_message_req)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_pse_message_req);
		ocalloc_size -= _len_pse_message_req;
	} else {
		ms->ms_pse_message_req = NULL;
	}
	
	ms->ms_pse_message_req_size = pse_message_req_size;
	if (pse_message_resp != NULL) {
		ms->ms_pse_message_resp = (uint8_t*)__tmp;
		__tmp_pse_message_resp = __tmp;
		memset(__tmp_pse_message_resp, 0, _len_pse_message_resp);
		__tmp = (void *)((size_t)__tmp + _len_pse_message_resp);
		ocalloc_size -= _len_pse_message_resp;
	} else {
		ms->ms_pse_message_resp = NULL;
	}
	
	ms->ms_pse_message_resp_size = pse_message_resp_size;
	ms->ms_timeout = timeout;
	status = sgx_ocall(18, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (pse_message_resp) {
			if (memcpy_s((void*)pse_message_resp, _len_pse_message_resp, __tmp_pse_message_resp, _len_pse_message_resp)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sgx_oc_cpuidex(int cpuinfo[4], int leaf, int subleaf)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_cpuinfo = 4 * sizeof(int);

	ms_sgx_oc_cpuidex_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_sgx_oc_cpuidex_t);
	void *__tmp = NULL;

	void *__tmp_cpuinfo = NULL;

	CHECK_ENCLAVE_POINTER(cpuinfo, _len_cpuinfo);

	ocalloc_size += (cpuinfo != NULL) ? _len_cpuinfo : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_sgx_oc_cpuidex_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_sgx_oc_cpuidex_t));
	ocalloc_size -= sizeof(ms_sgx_oc_cpuidex_t);

	if (cpuinfo != NULL) {
		ms->ms_cpuinfo = (int*)__tmp;
		__tmp_cpuinfo = __tmp;
		memset(__tmp_cpuinfo, 0, _len_cpuinfo);
		__tmp = (void *)((size_t)__tmp + _len_cpuinfo);
		ocalloc_size -= _len_cpuinfo;
	} else {
		ms->ms_cpuinfo = NULL;
	}
	
	ms->ms_leaf = leaf;
	ms->ms_subleaf = subleaf;
	status = sgx_ocall(19, ms);

	if (status == SGX_SUCCESS) {
		if (cpuinfo) {
			if (memcpy_s((void*)cpuinfo, _len_cpuinfo, __tmp_cpuinfo, _len_cpuinfo)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sgx_thread_wait_untrusted_event_ocall(int* retval, const void* self)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_sgx_thread_wait_untrusted_event_ocall_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_sgx_thread_wait_untrusted_event_ocall_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_sgx_thread_wait_untrusted_event_ocall_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_sgx_thread_wait_untrusted_event_ocall_t));
	ocalloc_size -= sizeof(ms_sgx_thread_wait_untrusted_event_ocall_t);

	ms->ms_self = self;
	status = sgx_ocall(20, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sgx_thread_set_untrusted_event_ocall(int* retval, const void* waiter)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_sgx_thread_set_untrusted_event_ocall_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_sgx_thread_set_untrusted_event_ocall_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_sgx_thread_set_untrusted_event_ocall_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_sgx_thread_set_untrusted_event_ocall_t));
	ocalloc_size -= sizeof(ms_sgx_thread_set_untrusted_event_ocall_t);

	ms->ms_waiter = waiter;
	status = sgx_ocall(21, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sgx_thread_setwait_untrusted_events_ocall(int* retval, const void* waiter, const void* self)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_sgx_thread_setwait_untrusted_events_ocall_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_sgx_thread_setwait_untrusted_events_ocall_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_sgx_thread_setwait_untrusted_events_ocall_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_sgx_thread_setwait_untrusted_events_ocall_t));
	ocalloc_size -= sizeof(ms_sgx_thread_setwait_untrusted_events_ocall_t);

	ms->ms_waiter = waiter;
	ms->ms_self = self;
	status = sgx_ocall(22, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sgx_thread_set_multiple_untrusted_events_ocall(int* retval, const void** waiters, size_t total)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_waiters = total * sizeof(void*);

	ms_sgx_thread_set_multiple_untrusted_events_ocall_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_sgx_thread_set_multiple_untrusted_events_ocall_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(waiters, _len_waiters);

	ocalloc_size += (waiters != NULL) ? _len_waiters : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_sgx_thread_set_multiple_untrusted_events_ocall_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_sgx_thread_set_multiple_untrusted_events_ocall_t));
	ocalloc_size -= sizeof(ms_sgx_thread_set_multiple_untrusted_events_ocall_t);

	if (waiters != NULL) {
		ms->ms_waiters = (const void**)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, waiters, _len_waiters)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_waiters);
		ocalloc_size -= _len_waiters;
	} else {
		ms->ms_waiters = NULL;
	}
	
	ms->ms_total = total;
	status = sgx_ocall(23, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL memccpy(void** retval, void* dest, const void* src, int val, size_t len)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_dest = len;
	size_t _len_src = len;

	ms_memccpy_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_memccpy_t);
	void *__tmp = NULL;

	void *__tmp_dest = NULL;

	CHECK_ENCLAVE_POINTER(dest, _len_dest);
	CHECK_ENCLAVE_POINTER(src, _len_src);

	ocalloc_size += (dest != NULL) ? _len_dest : 0;
	ocalloc_size += (src != NULL) ? _len_src : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_memccpy_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_memccpy_t));
	ocalloc_size -= sizeof(ms_memccpy_t);

	if (dest != NULL) {
		ms->ms_dest = (void*)__tmp;
		__tmp_dest = __tmp;
		if (memcpy_s(__tmp_dest, ocalloc_size, dest, _len_dest)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_dest);
		ocalloc_size -= _len_dest;
	} else {
		ms->ms_dest = NULL;
	}
	
	if (src != NULL) {
		ms->ms_src = (const void*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, src, _len_src)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_src);
		ocalloc_size -= _len_src;
	} else {
		ms->ms_src = NULL;
	}
	
	ms->ms_val = val;
	ms->ms_len = len;
	status = sgx_ocall(24, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (dest) {
			if (memcpy_s((void*)dest, _len_dest, __tmp_dest, _len_dest)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_function_allow(void)
{
	sgx_status_t status = SGX_SUCCESS;
	status = sgx_ocall(25, NULL);

	return status;
}
