#include <pb.h>

#include <stdio.h>

static uint8_t data[128 * 1024];

int main()
{
    struct proto_bug test;
    proto_bug_init(&test, data);

    proto_bug_write_uint8(&test, 100, "uint8_test");
    proto_bug_write_uint16(&test, 10000, "uint16_test");
    proto_bug_write_uint32(&test, 1000000000, "uint32_test");
    proto_bug_write_uint64(&test, 10000000000000, "uint64_test");
    proto_bug_write_float32(&test, 12341.0123f, "float32_test");
    proto_bug_write_float64(&test, 12341.01234f, "some float 64");
    proto_bug_write_varuint(&test, 100000000000000ull, "varuint_test");
    proto_bug_write_string(&test, "test string", 11, "string_test");
    proto_bug_reset(&test);
    uint8_t a = proto_bug_read_uint8(&test, "uint8_test");
    uint16_t b = proto_bug_read_uint16(&test, "uint16_test");
    uint32_t c = proto_bug_read_uint32(&test, "uint32_test");
    uint64_t d = proto_bug_read_uint64(&test, "uint64_test");
    float e = proto_bug_read_float32(&test, "float32_test");
    double f = proto_bug_read_float32(&test, "some float 32"); // oops!
    uint64_t g = proto_bug_read_varuint(&test, "varuint_test");
    char h[12] = {0};
    proto_bug_read_string(&test, h, 11, "string_test");
    printf("%u %u %u %lu %f %f %lu %s\n", a, b, c, d, e, f, g, h);
}
