// Example Metal shader
#include <metal_stdlib>
using namespace metal;

vertex float4 vertex_main(const device float4* vertexArray [[buffer(0)]],
                          uint vertexId [[vertex_id]]) {
    return vertexArray[vertexId];
}

fragment float4 fragment_main() {
    return float4(1.0, 0.0, 0.0, 1.0); // Red
}
