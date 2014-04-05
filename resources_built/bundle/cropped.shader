{
"VertexShader":"
	attribute vec2 a_position;
	attribute vec2 a_texturePosition;

	uniform mat3 u_transformation;
	uniform sampler2D u_texture;
	uniform float u_value;

	varying vec2 v_texturePosition;
	varying float v_cropLevel;
	varying float v_currentLevel;
	
	void main()
	{
		v_texturePosition = a_texturePosition;
		vec3 pos = vec3(a_position, 1.0) * u_transformation;
		v_cropLevel = u_value;
		v_currentLevel = a_position.y;
	#ifdef IOS
		gl_Position =  vec4(-pos.y, pos.x, 0.0, 1.0);
	#else
		gl_Position =  vec4(pos.x, pos.y, 0.0, 1.0);
	#endif
	}
"
,
"FragmentShader":"
	precision mediump float;
		
	uniform sampler2D u_texture;
	
	varying vec2 v_texturePosition;
	varying float v_cropLevel;
	varying float v_currentLevel;

	void main()
	{
		float crop = float(v_currentLevel < v_cropLevel);
		gl_FragColor = crop * texture2D(u_texture, v_texturePosition);
	}
"
}