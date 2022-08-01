#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <libXbSymbolDatabase.h>

static void msg_cb(xb_output_message message_flag, const char* msg)
{
    fprintf(stderr, "XbSymbolDatabase: %s\n", msg);
}

static void reg_cb(const char* library_str, uint32_t library_flag, uint32_t xref_index, const char* symbol_str, xbaddr address, uint32_t build_verison)
{
    printf("%.8s__%s = 0x%08x\n", library_str, symbol_str, address);
}

int main(int argc, char const* argv[])
{
    int verbose = 0;
    const char* xbe_path = NULL;
    int arg_off = 1;

    if (argc > 1 && strcmp(argv[1], "-verbose") == 0) {
        verbose = 1;
        arg_off++;
    }

    if (arg_off >= argc) {
        fprintf(stderr, "usage: %s [-verbose] xbefile\n", argv[0]);
        return 1;
    }
    else {
        xbe_path = argv[arg_off];
    }

    unsigned int version = XbSymbolDatabase_LibraryVersion();
    if (verbose) {
        fprintf(stderr, "Database Version = %x\n", version);
    }

    FILE* fd = fopen(xbe_path, "rb");
    if (fd == NULL) {
        fprintf(stderr, "failed to open %s for reading\n", xbe_path);
        return 1;
    }

    fseek(fd, 0, SEEK_END);
    size_t size = ftell(fd);
    rewind(fd);

    unsigned char* xbe = malloc(size);
    assert(xbe != NULL);
    size_t num_read = fread(xbe, 1, size, fd);
    assert(num_read == size);
    if (memcmp(xbe, "XBEH", 4) != 0) {
        fprintf(stderr, "invalid xbe header\n");
        free(xbe);
        return 1;
    }

    XbSymbolDatabase_SetOutputMessage(&msg_cb);

    if (verbose) {
        XbSymbolDatabase_SetOutputVerbosity(XB_OUTPUT_MESSAGE_DEBUG);
    }

    XbSDBLibraryHeader lib_hdr;
    lib_hdr.count = XbSymbolDatabase_GenerateLibraryFilter(xbe, NULL);
    lib_hdr.filters = malloc(lib_hdr.count * sizeof(XbSDBLibrary));
    assert(lib_hdr.filters != NULL);
    XbSymbolDatabase_GenerateLibraryFilter(xbe, &lib_hdr);

    if (verbose) {
        fprintf(stderr, "%u libraries\n", lib_hdr.count);
        for (unsigned int i = 0; i < lib_hdr.count; i++) {
            fprintf(stderr, "  %.8s\n", lib_hdr.filters[i].name);
        }
    }

    XbSDBSectionHeader sec_hdr;
    sec_hdr.count = XbSymbolDatabase_GenerateSectionFilter(xbe, NULL, 1);
    sec_hdr.filters = malloc(sec_hdr.count * sizeof(XbSDBSection));
    assert(sec_hdr.filters != NULL);
    XbSymbolDatabase_GenerateSectionFilter(xbe, &sec_hdr, 1);

    if (verbose) {
        fprintf(stderr, "%u sections\n", sec_hdr.count);
        for (unsigned int i = 0; i < sec_hdr.count; i++) {
            fprintf(stderr, "  %.8s\n", sec_hdr.filters[i].name);
        }
    }

    XbSymbolContextHandle ctx;
    bool status = XbSymbolDatabase_CreateXbSymbolContext(&ctx,
                                                         reg_cb,
                                                         lib_hdr,
                                                         sec_hdr,
                                                         XbSymbolDatabase_GetKernelThunkAddress(xbe));
    assert(status == 1);
    XbSymbolContext_ScanManual(ctx);
    XbSymbolContext_ScanAllLibraryFilter(ctx);
    XbSymbolContext_RegisterXRefs(ctx);
    XbSymbolContext_Release(ctx);

    free(lib_hdr.filters);
    free(sec_hdr.filters);
    free(xbe);
    return 0;
}
