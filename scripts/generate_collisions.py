import Image, json, sys, os
from numpy import pi, arctan, array

# Created by Oleksandr Kuznietsov 25.01.14
# Mail: o.kuznietsov@gmail.com

# Requires python2.7, with PIL and numpy modules installed
# Usage: python generate_collisions.py ../resources/collisions ../resources_built
# All PNG files in folder specified as first argument will be parsed for collisions
# and stored with same name (but with .ctf extension) in folder specified as second argument

# Script generates collision triangle fan (.ctf) file from PNG image using JSON notation
# Input PNG files should have white background and contain one red point as center of the 
# object and various number of blue points as vertices of the resukting fan of triangles
# CTF file contains an array of described pixel coordinates starting from center point,
# then rest of vertices sorted clockwise from center point. Triangle fan is not complete
# for full object coverage it should create one more triangle using first and last vertices

def dot(a,b):
	return a[0]*b[0] + a[1]*b[1]

def sub(a,b):
	return [a[0]-b[0], a[1]-b[1]]

def sum(a,b):
	return [a[0]+b[0], a[1]+b[1]]

def angle(v):
	if (v[0] == 0):
		if (v[1] > 0):
			return 0
		else:
			return pi
	if (v[1] == 0):
		if (v[0] > 0):
			return pi/2
		else:
			return pi + pi/2
	if (v[1] > 0):
		return arctan(v[0]/v[1])
	else:
		if(v[0] > 0):
			return pi + arctan(v[0]/v[1])
		else:
			return pi + arctan(v[1]/v[0])

def find_and_sort(filename):
	im = Image.open(filename)
	im.load()
	ar = array(im)

	size = [1.0*a for a in im.size]
	center = [a/2.0 for a in size]
	verts = []
	for i, row in enumerate(ar):
		for j, px in enumerate(row):
			if px[2] == 0:
				center = [i, j]
			elif px[0] == 0:
				verts.append([i, j])

	verts_n = []
	for i, v in enumerate(verts):
		verts_n.append(sub(v,center))

	verts_n = sorted(verts_n, key = angle)

	ret = [center]
	for i, v in enumerate(verts_n):
		ret.append(sum(v, center))

	return ret

def main(file_from, file_to):
	fan = find_and_sort(file_from)
	collision_file = open(file_to, "w")
	collision_file.write(json.dumps(fan))
	collision_file.close()

if __name__ == '__main__':
	path_from = sys.argv[1]
	path_to = sys.argv[2]
	all_files = [f for f in os.listdir(path_from) if os.path.isfile(os.path.join(path_from, f))]
	files = [os.path.splitext(f)[0] for f in all_files if os.path.splitext(f)[1] == '.png']
	for f in files:
		print("Generating {0}.ctf".format(f))
		file_from = os.path.join(path_from, f + '.png')
		file_to = os.path.join(path_to, f + '.ctf')
		main(file_from, file_to)