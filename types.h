#ifndef  type_h
#define type_h
typedef enum types
{
    success = 0, 
    failure = -1
} status;
typedef enum operation
{
    view,
    edit,
    unsupported
}operation_type;
#endif
