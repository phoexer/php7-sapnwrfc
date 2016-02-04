/*
 +----------------------------------------------------------------------+
 | PHP Version 7                                                        |
 +----------------------------------------------------------------------+
 | Copyright (c) 2015 Gregor Kralik                                     |
 +----------------------------------------------------------------------+
 | This source file is subject to version 3.01 of the PHP license,      |
 | that is bundled with this package in the file LICENSE, and is        |
 | available through the world-wide-web at the following url:           |
 | http://www.php.net/license/3_01.txt                                  |
 | If you did not receive a copy of the PHP license and are unable to   |
 | obtain it through the world-wide-web, please send a note to          |
 | license@php.net so we can mail you a copy immediately.               |
 +----------------------------------------------------------------------+
 | Author: Gregor Kralik <g.kralik@gmail.com>                           |
 +----------------------------------------------------------------------+
 */

#include "php.h"
#include "sapnwrfc.h"


SAP_UC *char_to_sapuc(char *str)
{
    RFC_ERROR_INFO error_info;
    SAP_UC *sapuc;
    unsigned sapuc_size, result_length = 0;

    sapuc_size = strlen(str) + 1;
    sapuc = callocU(1, sapuc_size);
    RfcUTF8ToSAPUC((RFC_BYTE *) str, strlen(str), sapuc, &sapuc_size,
            &result_length, &error_info);
    return sapuc;
}

SAP_UC *zend_string_to_sapuc(zend_string *str)
{
    RFC_ERROR_INFO error_info;
    SAP_UC *sapuc;
    unsigned sapuc_size, result_length = 0;

    sapuc_size = ZSTR_LEN(str) + 1;
    sapuc = callocU(1, sapuc_size);

    RfcUTF8ToSAPUC((RFC_BYTE *) ZSTR_VAL(str), ZSTR_LEN(str), sapuc,
            &sapuc_size, &result_length, &error_info);
    return sapuc;
}

zend_string *sapuc_to_zend_string(SAP_UC *str)
{
    RFC_ERROR_INFO error_info;
    unsigned utf8size, result_length;
    char *utf8;
    zend_string *out;

    utf8size = strlenU(str) * 4;
    utf8 = calloc(1, utf8size + 2);

    result_length = 0;
    RfcSAPUCToUTF8(str, strlenU(str), (RFC_BYTE *)utf8, &utf8size, &result_length, &error_info);

    out = zend_string_init(utf8, result_length, 0);
    free(utf8);

    return out;
}