#define _CRT_SECURE_NO_DEPRECATE
#include <windows.h>
//#include <mimalloc.h>
#include <stdio.h>
#include <intrin.h>
//#include <time.h>

//C:\Users\mictb\Downloads\mimalloc-2.0.9\mimalloc-2.0.9\out\msvc-x64\Release>cl /MD /Iinclude harnessJP2.c mimalloc-static.lib Advapi32.lib /link /out:harnessJP2.exe /SUBSYSTEM:CONSOLE

#pragma intrinsic(_ReturnAddress)



void dump_mem(void* p, int size)
{
    printf("Memory @ %#x, size: %d", p, size);
    size = size > 0x100 ? 0x100 : size;
    for (int i = 0; i < size; i++)
    {
        if (i % 16 == 0) { printf("\n"); }
        printf("%02x ", *((BYTE*)p + i));
    }
    printf("\n");
}

typedef struct file_custom
{
    INT64 pos;
    char* bytes;
    size_t fileLen;
}file_;


size_t read_(file_* fd, void* buf, size_t count)
{

    unsigned int end = (fd->pos + count > fd->fileLen) ? fd->fileLen : fd->pos + count;
    unsigned int bytesWritten = end - fd->pos;

    // printf("bytes_written: %d\n", bytesWritten);
    memcpy(buf, fd->bytes + fd->pos, bytesWritten);
    fd->pos += bytesWritten;
    return bytesWritten;

}


int seek_(file_* fd, int flag, signed int newPos) {
   // printf("old pos = %d and newArg = %d\n", fd->pos,newPos);
    switch (flag)
    { // Adobe uses different SEEK constants than the ones defined in libc
    case 0:
        // relative seek
        fd->pos += newPos;
        if (fd->pos > fd->fileLen)
        {
            fd->pos = fd->fileLen;
        }
        break;


    case 1:
        // absolute seek
        fd->pos = newPos;
        if (fd->pos > fd->fileLen)
        {
            fd->pos = fd->fileLen;
        }
        break;

    default:
        printf("[x] ERR_NOT_IMPLEMENTED - seek flag %d", flag);
    }
   //  printf("now pos = %d\n",fd->pos);
    return fd->pos;
}

LONG64* init_something(LONG64* foo)
{
    //  printf("[i] called 1 with arg: %p\n", foo);
    return foo;
}


INT16 is_writable(file_* x)
{
    //  printf("is write\n");
    if (x->bytes == 0)
    {
     //    printf("not writable???\n");
        return 0;
    }
    return 1;
}

INT16 is_readable(file_* x)
{
    // printf("is read\n");
    if (x->bytes == 0)
    {
        // printf("not readable???\n");
        return 0;
    }
    return 1;
}

INT16 is_seekable(file_* x)
{
    //  printf("is seek with %p\n",x);
    if (x->bytes == 0)
    {
       //  printf("not seekable???\n");
        return 0;
    }
    return 1;
}

int tell_(file_* x)
{
    // printf("tell \n");
    return x->pos;
}



typedef struct
{
    INT64 x;
    INT64 s;
    void* z;

}some_inside;


typedef struct
{
    INT64 x;
    void* i;
    void* z;
    INT64 s;

}some;


typedef struct
{
    void* funcs[9];
} vtable_t;



typedef INT64(*JP2KLibInitEx_func_t)(vtable_t*);

typedef void* (*JP2KGetMemObjEx_func_t)();
typedef void* (*JP2KEncOptDestroy_func_t)(INT64*);
typedef void* (*JP2KDecOptCreate_func_t)();
typedef void* (*JP2KImageCreate_func_t)();
typedef INT64(*JP2KImageDecodeTileInterleaved_func_t)(void*, INT16, INT64, INT16, INT64, INT16, void*);
typedef INT64(*JP2KImageGetMaxRes_func_t)(void*);
typedef void* (*JP2KImageDataCreate_func_t)();
typedef byte(*JP2KDecOptInitToDefaults_func_t)(void*);
typedef INT64(*JP2KImageInitDecoderEx_func_t)(void*, file_*, vtable_t*, void*, void*);
typedef INT32(*JP2KImageDataDestroy_func_t)(void*);
typedef INT32(*JP2KImageDestroy_func_t)(void*);
typedef INT32(*JP2KDecOptDestroy_func_t)(void*);
typedef INT32 (*JP2KLibShutDown_func_t)(void);


JP2KLibShutDown_func_t JP2KLibShutDown_func;
JP2KImageInitDecoderEx_func_t JP2KImageInitDecoderEx_func;
JP2KImageCreate_func_t JP2KImageCreate_func;
JP2KEncOptDestroy_func_t JP2KEncOptDestroy_func;
JP2KDecOptInitToDefaults_func_t JP2KDecOptInitToDefaults_func;
JP2KDecOptCreate_func_t JP2KDecOptCreate_func;
JP2KGetMemObjEx_func_t JP2KGetMemObjEx_func;
JP2KLibInitEx_func_t JP2KLibInitEx_func;
JP2KImageDataCreate_func_t JP2KImageDataCreate_func;
JP2KImageGetMaxRes_func_t JP2KImageGetMaxRes_func;
JP2KImageDecodeTileInterleaved_func_t JP2KImageDecodeTileInterleaved_func;
JP2KImageDataDestroy_func_t JP2KImageDataDestroy_func;
JP2KImageDestroy_func_t JP2KImageDestroy_func;
JP2KDecOptDestroy_func_t JP2KDecOptDestroy_func;


#define NOP(x) \
    int nop##x(){  \
        return (DWORD)x; \
}// printf("==> nop%d called, %p\n", ##x, _ReturnAddress()); \





NOP(0);
NOP(1);
NOP(2);
NOP(3);
NOP(4);
NOP(5);
NOP(6);
NOP(7);
NOP(8);


NOP(11);
NOP(22);
NOP(33);
NOP(44);
NOP(55);
NOP(66);
NOP(77);
NOP(88);
NOP(99);


NOP(12);
NOP(13);
NOP(14);
NOP(15);
NOP(16);
NOP(17);
NOP(18);
NOP(19);
NOP(10);



void free_1(void* ptr)
{
    // printf("[i] MemObj::free() - src:%p \n", ptr);
    return free(ptr);
}

void* memcpy_1(void* dest, void* src, size_t n)
{
    // printf("[i] MemObj::memcpy() - dest:%p   src:%p   size:0x%x\n", dest, src, n);
    return memcpy(dest, src, n);
}

void* malloc_1(int size)
{
    void* allocation = malloc(size);
     // printf("[i] MemObj::alloc() - allocated 0x%x bytes at %p\n", size, allocation);
    return allocation;
}

void* memset_wrapper(void* dest, int val, int size)
{
    //printf("[i] MemObj::memset() - dest:%p   val:0x%x   size:0x%x\n", dest, val, size);
    return memset(dest, val, size);;

}

//void* big = NULL;

//int to int64


void* something(INT64 size)
{
   // printf("called to malloc something %x\n", size);
    some_inside* inside = malloc((sizeof(some_inside)));
    some* newsome = malloc((sizeof(some)));


    void* zz = NULL;
    zz = malloc(size);

    /*
    if(size > 0x90000)
    {
        int ii;
        free(big);
        free(source);
        printf("stopPPP size overhead\n");
        scanf("asdf %d\n",&ii);
        exit(1);
    }
    else
    {
        zz = big;
    }*/

    inside->x = 1;
    inside->s = size;
    inside->z = zz;

    newsome->x = 0;
    newsome->i = &((*inside).x);
    newsome->z = zz;
    newsome->s = size;

    // printf("the stuct = %p and heap = %p\n", &(*newsome), zz);

    return &(*newsome);
}

void* something2(INT64* some2)
{
   // passed something
    //printf("something2\n");
    void* ahhhhhhhhhhhhh = *(some2 + 2);
   // printf("heap correct ? = %p\n", ahhhhhhhhhhhhh);
    return ahhhhhhhhhhhhh;
}

void nop222(LONG64 x) 
{
    return 0;
}

void nop3_v1()
{
  //  printf("nop3\n");
    return 0;
}

void nop4_v1(INT64* structt)
{
  //  printf("nop4 something clear\n");

    void* ahhhhhhhhhhhhh = *(structt + 2);
    void* a2 = *(structt + 1);

    // printf("clearing struct = %p and heap = %p\n", structt, ahhhhhhhhhhhhh);

    free(ahhhhhhhhhhhhh);
    free(a2);

    free(structt);
    return 0;
}


vtable_t vtbl3;
HMODULE hJp2klib;



__declspec(dllexport) void __cdecl fuzzme(char* filename);

void fuzzme(char* filename)
{
    void* mem = JP2KGetMemObjEx_func();

    void* dopt = JP2KDecOptCreate_func();




    byte optinitTo = JP2KDecOptInitToDefaults_func(dopt);




    void* ImgCreate = JP2KImageCreate_func();



    file_ obj;
    /////////////////

    char* source = NULL;
    size_t newLen = 0;
    long bufsize = 0;


    FILE* fp = fopen(filename, "rb");
    if (fp != NULL) {
        /* Go to the end of the file. */
        if (fseek(fp, 0L, SEEK_END) == 0) {
            /* Get the size of the file. */
            bufsize = ftell(fp);
            if (bufsize == -1) { printf("neg buff size\n"); return; }

            /* Allocate our buffer to that size. */
            source = malloc(sizeof(char) * (bufsize + 1));

            /* Go back to the start of the file. */
            if (fseek(fp, 0, SEEK_SET) != 0) { printf("seek fail \n"); return; }

            /* Read the entire file into memory. */
            newLen = fread(source, sizeof(char), bufsize, fp);

            if (ferror(fp) != 0) {
                fputs("Error reading file", stderr);
            }
            else {

                source[newLen++] = '\0'; /* Just to be safe. */
            }
        }
        fclose(fp);
    }


    obj.bytes = source;
    obj.fileLen = bufsize;
    obj.pos = 0;


    void* memm = malloc(0x100);
   // printf("befreeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n");
    int aa = JP2KImageInitDecoderEx_func(ImgCreate, &obj, &vtbl3, dopt, memm); //question
  //  printf("JP2KImageInitDecoderEx_func: ret = %p\n\n", aa);

  //  printf("calling dataCreate\n");
    void* DataC = JP2KImageDataCreate_func();
  //  printf("calling maxres\n");
    int maxres = JP2KImageGetMaxRes_func(ImgCreate);
   // printf("calling decLeav\n");
    int ret = JP2KImageDecodeTileInterleaved_func(ImgCreate, 0, maxres, 8, 0xff, 00, DataC);
   // printf("JP2KImageDecodeTileInterleaved_func: ret = %d\n\n", ret);
 

  //  printf("calling DataDestroy\n");
   JP2KImageDataDestroy_func(DataC);
 //  printf("calling ImageDestroy\n");
    JP2KImageDestroy_func(ImgCreate);

   // printf("calling enc_destroy = %p\n", *((INT64*)dopt + 3));
    JP2KEncOptDestroy_func(*((INT64*)dopt + 3));

 //   printf("calling DecOptDestroy\n");
    JP2KDecOptDestroy_func(dopt);

    free(memm);
    free(source);


    printf("EXITING ret fuzzme\n");

    return;

}


int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage %s: <input file>\n", argv[0]);
        // argv[1] = "C:\\Users\\mictb\\OneDrive\\Desktop\\in\\relax.jp2";
        return 1;
    }

    vtable_t vtbl;
    vtbl.funcs[0] = something;
    vtbl.funcs[1] = something2;
    vtbl.funcs[2] = nop3_v1;
    vtbl.funcs[3] = nop4_v1;
    vtbl.funcs[4] = malloc_1;
    vtbl.funcs[5] = free_1;//
    vtbl.funcs[6] = memcpy_1;//
    vtbl.funcs[7] = memset_wrapper;
    vtbl.funcs[8] = free_1;


    vtbl3.funcs[0] = init_something;
    vtbl3.funcs[1] = nop222;//nop
    vtbl3.funcs[2] = read_;
    vtbl3.funcs[3] = nop33;
    vtbl3.funcs[4] = seek_;
    vtbl3.funcs[5] = tell_;
    vtbl3.funcs[6] = is_seekable;
    vtbl3.funcs[7] = is_readable;
    vtbl3.funcs[8] = is_writable;


    hJp2klib = LoadLibraryA("JP2KLib.dll");
    if (hJp2klib == NULL)
    {
        printf("failed to load lib, gle = %d\n", GetLastError());
        exit(1);
    };


    JP2KImageInitDecoderEx_func = GetProcAddress(hJp2klib, "JP2KImageInitDecoderEx");
    if (!JP2KImageInitDecoderEx_func) {

        printf("failed to load function 1\n");
        exit(1);
    }

    JP2KImageCreate_func = GetProcAddress(hJp2klib, "JP2KImageCreate");
    if (!JP2KImageCreate_func) {

        printf("failed to load function2 \n");
        exit(1);
    }


    JP2KDecOptInitToDefaults_func = GetProcAddress(hJp2klib, "JP2KDecOptInitToDefaults");
    if (!JP2KDecOptInitToDefaults_func) {

        printf("failed to load function3 \n");
        exit(1);
    }


    JP2KDecOptCreate_func = GetProcAddress(hJp2klib, "JP2KDecOptCreate");
    if (!JP2KDecOptCreate_func) {

        printf("failed to load function5 \n");
        exit(1);
    }


    JP2KGetMemObjEx_func = GetProcAddress(hJp2klib, "JP2KGetMemObjEx");
    if (!JP2KGetMemObjEx_func) {

        printf("failed to load function6 \n");
        exit(1);
    }

    JP2KLibInitEx_func = GetProcAddress(hJp2klib, "JP2KLibInitEx");
    if (!JP2KLibInitEx_func) {

        printf("failed to load function7 \n");
        exit(1);
    }

    JP2KImageDataCreate_func = GetProcAddress(hJp2klib, "JP2KImageDataCreate");
    if (!JP2KImageDataCreate_func) {

        printf("failed to load function7 \n");
        exit(1);
    }


    JP2KImageGetMaxRes_func = GetProcAddress(hJp2klib, "JP2KImageGetMaxRes");
    if (!JP2KImageGetMaxRes_func) {

        printf("failed to load function7 \n");
        exit(1);
    }

    JP2KImageDecodeTileInterleaved_func = GetProcAddress(hJp2klib, "JP2KImageDecodeTileInterleaved");
    if (!JP2KImageDecodeTileInterleaved_func) {

        printf("failed to load function7 \n");
        exit(1);
    }

    JP2KImageDataDestroy_func = GetProcAddress(hJp2klib, "JP2KImageDataDestroy");
    if (!JP2KImageDataDestroy_func) {

        printf("failed to load function7 \n");
        exit(1);
    }

    JP2KImageDestroy_func = GetProcAddress(hJp2klib, "JP2KImageDestroy");
    if (!JP2KImageDestroy_func) {

        printf("failed to load function7 \n");
        exit(1);
    }


    JP2KEncOptDestroy_func = GetProcAddress(hJp2klib, "JP2KEncOptDestroy");
    if (!JP2KEncOptDestroy_func) {

        printf("failed to load function7 \n");
        exit(1);
    }




    JP2KDecOptDestroy_func = GetProcAddress(hJp2klib, "JP2KDecOptDestroy");
    if (!JP2KDecOptDestroy_func) {

        printf("failed to load function7 \n");
        exit(1);
    }


    JP2KLibShutDown_func = GetProcAddress(hJp2klib, "JP2KLibShutDown");
    if (!JP2KLibShutDown_func) {

        printf("failed to load function7 \n");
        exit(1);
    }



    int ret = JP2KLibInitEx_func(&vtbl);

    //  int i = 0;
    //  float startTime = (float)clock() / CLOCKS_PER_SEC;
    //  while(1)
   //   {
    fuzzme(argv[1]);
   //  i++;
 /// }
 // free(big);
  //float endTime = (float)clock() / CLOCKS_PER_SEC;

//  float timeElapsed = endTime - startTime;

  //printf("time elapsed = %f\n", timeElapsed);
    //  exit(0);

      JP2KLibShutDown_func();
   //   printf("done\n");

    return 0;

}


