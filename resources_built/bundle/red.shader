{
"VertexShader":"
	attribute vec2 a_position;

	uniform vec3 u_blendColor;
	
	void main()
	{
		vec3 pos = vec3(a_position, 1.0) * u_transformation;
		gl_Position =  vec4(pos, 1.0);
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