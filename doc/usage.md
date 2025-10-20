# Usage

### Basic structure

```cpp
// The returned integer should be 0 or greater
// on success. It should be less than 0 (negative)
// if an error occurred.
int make_string(
    // If the function allocates memory for the caller,
    // its first parameter should be a double pointer
    // whose value should be a pointer to the newly
    // allocated memory after successful execution.
    char** out,
    int length, // other parameters can follow ...
) {
    // We must declare an integer named `ret_code` that
    // will be returned by this function.
    int ret_code = 0;
    char *str = NULL; // other variables ...
    char *buffer = NULL;

    if (0 == length) {
        // Return early since we don't need to anything.
        return_ok(0);
    }

    // Should `printf()` fail and return a negative value,
    // the returned value is set as the return code and
    // control flow jumps to `on_error:` below.
    return_err(printf("Making the string"));

    // If instead we would like to return a specific error...
    return_err_ext(printf("Doing it..."), -2);

    str = malloc(length);
    if (NULL == str) {
        // Memory allocation failed. Return an error
        // immediately (i.e. -1 for example).
        // Control will jump to `on_error:` below.
        return_err_now(-1);
    }

    // Assign allocated memory. Caller is
    // responsible for freeing it.
    *out = str;

on_error: // Must be defined before cleanup:
    // Cleanup actions in case an error occurs
    // anywhere in this function. You usually free
    // memory that was to be returned to the caller.
    if (NULL != str) free(str);

cleanup:
    // Cleanup actions that are always performed.
    // You should free any temporary memory allocated
    // during both success and failure scenarios.
    if (NULL != buffer) free(buffer);

    return ret_code; // The return code.
}
```

### Assertions

When using any of the assertions functions, such as
`contra_assert_ok()`, you can enable assertions by defining the `NDEBUG`
preprocessor variable.

### Tests

To disable tests that rely on the network, define the
`CONTRA_TEST_NO_NETWORK` preprocessor variable.
