{
"VertexShader":"
	attribute vec2 a_position;
	attribute vec2 a_texturePosition;

	uniform mat3 u_transformation;
	uniform vec3 u_blendColor;
	uniform sampler2D u_texture;

	varying vec2 v_texturePosition;
	
	void main()
	{
		v_texturePosition = a_texturePosition;
		vec3 pos = vec3(a_position, 1.0) * u_transformation;
		gl_Position =  vec4(pos, 1.0);
	}
"
,
"FragmentShader":"
	precision mediump float;
		
	uniform vec3 u_blendColor;
	uniform sampler2D u_texture;

	varying vec2 v_texturePosition;

	float softBlend(float a, float base)
	{
		return (
				(a < 0.5) 
				?
				(2.0 * base * a + base * base * (1.0 - 2.0 * a)) 
				:
				(sqrt(base) * (2.0 * a - 1.0) + 2.0 * base * (1.0 - a))
				);
	}
	void main()
	{
		vec4 fragmentColor = texture2D(u_texture, v_texturePosition);
		float luma = (0.2126*fragmentColor.r) + (0.7152*fragmentColor.g) + (0.0722*fragmentColor.b);
		gl_FragColor = vec4(
			softBlend(u_blendColor.r, fragmentColor.r * fragmentColor.a),
			softBlend(u_blendColor.g, fragmentColor.g * fragmentColor.a),
			softBlend(u_blendColor.b, fragmentColor.b * fragmentColor.a),
			fragmentColor.a
			);
	}
"
}