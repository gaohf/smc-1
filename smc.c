/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 321634 2012-01-01 13:15:04Z felipe $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_smc.h"

/* If you declare any globals in php_smc.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(smc)
*/

/* True global resources - no need for thread safety here */
static int le_smc;

zend_class_entry *smc_class_ce;

/* {{{ smc_functions[]
 *
 * Every user visible function must have an entry in smc_functions[].
 */
const zend_function_entry smc_functions[] = {
		PHP_ME(smc,get,NULL,ZEND_ACC_PUBLIC)
		PHP_ME(smc,add,NULL,ZEND_ACC_PUBLIC)
		PHP_ME(smc,delete,NULL,ZEND_ACC_PUBLIC)
		PHP_FE_END
};
/* }}} */

/* {{{ smc_module_entry
 */
zend_module_entry smc_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"smc",
	smc_functions,
	PHP_MINIT(smc),
	PHP_MSHUTDOWN(smc),
	PHP_RINIT(smc),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(smc),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(smc),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SMC
ZEND_GET_MODULE(smc)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("smc.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_smc_globals, smc_globals)
    STD_PHP_INI_ENTRY("smc.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_smc_globals, smc_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_smc_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_smc_init_globals(zend_smc_globals *smc_globals)
{
	smc_globals->global_value = 0;
	smc_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(smc)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	zend_class_entry smc_ce;
	/*初始化smc类*/
	INIT_CLASS_ENTRY(smc_ce, "smc", smc_functions);
	/*注册smc类   smc_class_ce是smc类实例化后可以用*/
	smc_class_ce = zend_register_internal_class(&smc_ce TSRMLS_CC);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(smc)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(smc)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(smc)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(smc)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "smc support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_smc_compiled(string arg)
   Return a string to confirm that the module is compiled in */
/*PHP_FUNCTION(confirm_smc_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "smc", arg);
	RETURN_STRINGL(strg, len, 0);
}*/
/*新增cache*/
PHP_METHOD(smc,add){
	char *key, *value = NULL;
	int key_len, value_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &key, &key_len, &value, &value_len) == FAILURE)
		WRONG_PARAM_COUNT;
	php_printf("key is %s, value is %s",key,value);
}
/*删除cache*/
PHP_METHOD(smc,delete){
	char *key = NULL;
	int key_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &key_len) == FAILURE)
		WRONG_PARAM_COUNT;
	php_printf("delete key is %s",key);
}
/*取得cache*/
PHP_METHOD(smc,get){
	char *key = NULL;
	int key_len;
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &key_len) == FAILURE)
			WRONG_PARAM_COUNT;
	php_printf("get key is %s",key);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
