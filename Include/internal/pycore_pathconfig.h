#ifndef Py_INTERNAL_PATHCONFIG_H
#define Py_INTERNAL_PATHCONFIG_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef Py_BUILD_CORE
#  error "Py_BUILD_CORE must be defined to include this header"
#endif

PyAPI_FUNC(void) _Py_wstrlist_clear(
    int len,
    wchar_t **list);
PyAPI_FUNC(wchar_t**) _Py_wstrlist_copy(
    int len,
    wchar_t **list);
PyAPI_FUNC(_PyInitError) _Py_wstrlist_append(
    int *len,
    wchar_t ***list,
    const wchar_t *str);
PyAPI_FUNC(PyObject*) _Py_wstrlist_as_pylist(
    int len,
    wchar_t **list);

typedef struct _PyPathConfig {
    /* Full path to the Python program */
    wchar_t *program_full_path;
    wchar_t *prefix;
#ifdef MS_WINDOWS
    wchar_t *dll_path;
#else
    wchar_t *exec_prefix;
#endif
    /* Set by Py_SetPath(), or computed by _PyPathConfig_Init() */
    wchar_t *module_search_path;
    /* Python program name */
    wchar_t *program_name;
    /* Set by Py_SetPythonHome() or PYTHONHOME environment variable */
    wchar_t *home;
    /* isolated and site_import are used to set Py_IsolatedFlag and
       Py_NoSiteFlag flags on Windows in read_pth_file(). These fields
       are ignored when their value are equal to -1 (unset). */
    int isolated;
    int site_import;
} _PyPathConfig;

#define _PyPathConfig_INIT \
    {.module_search_path = NULL, \
     .isolated = -1, \
     .site_import = -1}
/* Note: _PyPathConfig_INIT sets other fields to 0/NULL */

PyAPI_DATA(_PyPathConfig) _Py_path_config;

PyAPI_FUNC(void) _PyPathConfig_ClearGlobal(void);
PyAPI_FUNC(_PyInitError) _PyPathConfig_SetGlobal(
    const struct _PyPathConfig *config);

PyAPI_FUNC(_PyInitError) _PyPathConfig_Calculate_impl(
    _PyPathConfig *config,
    const _PyCoreConfig *core_config);
PyAPI_FUNC(PyObject*) _PyPathConfig_ComputeArgv0(int argc, wchar_t **argv);
PyAPI_FUNC(int) _Py_FindEnvConfigValue(
    FILE *env_file,
    const wchar_t *key,
    wchar_t *value,
    size_t value_size);

#ifdef __cplusplus
}
#endif
#endif /* !Py_INTERNAL_PATHCONFIG_H */
