//
//  Shader.fsh
//  AdmiralVsAsteroids
//
//  Created by Alexander Kuznietsov on 1/22/14.
//  Copyright (c) 2014 Alexander Kuznietsov. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
