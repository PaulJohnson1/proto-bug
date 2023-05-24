#  ProtoBug
ProtoBug is a C library designed to track down errors in a binary game protocol. It provides opt-out detailed error messages that help identify and debug issues in the protocol.
## Usage
To use the ProtoBug Library in your C project, follow these steps:
### Clone the repository or download the library files.
`git clone https://github.com/PaulJohnson1/proto-bug`
### Include the library header file in your code:
```c
#include <pb.h>
```
### Initializing the proto_bug struct:
 ```c
 static uint8_t  data[128 * 1024];
 struct proto_bug test;
 proto_bug_init(&test, data);
 ```
### Writing data:
 ```c
 proto_bug_write_uint8(&test, 100, "uint8_test");
proto_bug_write_uint16(&test, 10000, "uint16_test");
proto_bug_write_uint32(&test, 1000000000, "uint32_test");
proto_bug_write_uint64(&test, 10000000000000, "uint64_test");
proto_bug_write_float32(&test, 12341.0123f, "float32_test");
proto_bug_write_float64(&test, 12341.01234, "some float 64");
proto_bug_write_varuint(&test, 100000000000000ull, "varuint_test");
proto_bug_write_string(&test, "test string", 11, "string_test");
```
### Reading data:
```c
uint8_t a = proto_bug_read_uint8(&test, "uint8_test");
uint16_t b = proto_bug_read_uint16(&test, "uint16_test");
uint32_t c = proto_bug_read_uint32(&test, "uint32_test");
uint64_t d = proto_bug_read_uint64(&test, "uint64_test");
float e = proto_bug_read_float32(&test, "float32_test");
float f = proto_bug_read_float32(&test, "some float 32"); // oops!
uint64_t g = proto_bug_read_varuint(&test, "varuint_test");
char h[12] = {0};
proto_bug_read_string(&test, h, 11 /* bytes to read */, "string_test");
```

## Error Message Format
The library outputs error messages in the following format:
The error message consists of two parts:
1. **Expected**: `{encoding_type:float64 name:some float 64 written_at: test.c:24}`: This part represents the expected value or data type that the program attempted to read.
2. **Actual**: `{encoding_type:float32 name:some float 32 read_at: test.c:33}`: This part represents the actual value or data type that was encountered during the read operation.