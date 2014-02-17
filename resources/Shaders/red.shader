{
"VertexShader":"
	attribute vec2 a_position;
	attribute vec2 a_texturePosition;

	uniform mat3 u_transformation;
	
	void main()
	{
		vec3 pos = vec3(a_position, 1.0) * u_transformation;
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
	
	void main()
	{
		gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	}
"
}