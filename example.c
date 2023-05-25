#include <pb.h>

#include <stdio.h>

static uint8_t data[128 * 1024];

struct position
{
    float x;
    float y;
};

int main()
{
    struct proto_bug test;
    proto_bug_init(&test, data);

    struct position server_position = {100.0f, 50.0f};

    // encode
    proto_bug_write_float32(&test, server_position.x, "x position");
    proto_bug_write_float32(&test, server_position.y, "y position");

    // emulate the client receiving a new message and decoding
    proto_bug_reset(&test);

    struct position client_position;
    client_position.x = proto_bug_read_float32(&test, "x position");
    client_position.y = proto_bug_read_float32(&test, "y position");

    // emulate a client that didn't read the message correctly (it flipped x and y on accident)
    proto_bug_reset(&test);

    struct position faulty_client_position;
    faulty_client_position.y = proto_bug_read_float32(&test, "y position"); // error! (reading x position as if it were y positon)
    faulty_client_position.x = proto_bug_read_float32(&test, "x position");
}
