// Red/Blue glasses stereo, also known as anaglyph.
//
// NOTE: Will only be compiled for Vulkan so doesn't follow all the usual conventions.

uniform sampler2DArray sampler0;
varying vec2 v_texcoord0;

uniform vec4 u_setting;

void main() {
	// To be adjusted. Used to desaturate colors.
	vec3 grayDot = vec3(0.35, 0.5, 0.15);
	// And these are the output color channels.
	vec3 red = vec3(1.0, 0.0, 0.0);
	vec3 blue = vec3(0.0, 0.0, 1.0);
	// We should probably add the ability to tint the blue one between blue and green
	// to match whatever glasses the user has. Not sure if there's any win to adjusting red.

	vec3 left = texture(sampler0, vec3(v_texcoord0, 0.0)).xyz;
	vec3 right = texture(sampler0, vec3(v_texcoord0, 1.0)).xyz;

	float leftGray = dot(left, grayDot);
	float rightGray = dot(right, grayDot);

	float saturation = u_setting.x;

	vec3 leftColor = mix(vec3(leftGray), left, saturation) * red;
	vec3 rightColor = mix(vec3(rightGray), right, saturation) * blue;

	// TODO: Do something to gamma, maybe?

	gl_FragColor.rgb = leftColor + rightColor;
	gl_FragColor.a = 1.0;
}
