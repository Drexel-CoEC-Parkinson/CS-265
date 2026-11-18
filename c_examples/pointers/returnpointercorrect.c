/* 1. Return the value itself */
int foo1(int i)
{
    return i + 3;
}

/* 2. Let the caller supply the storage (as on slide 56) */
void foo2(int i, int *result)
{
    *result = i + 3;
}

/* 3. Allocate on the heap; the caller must free it */
int *foo3(int i)
{
    int *r = malloc(sizeof(int));

    if (r != NULL)
        *r = i + 3;
    return r;
}
