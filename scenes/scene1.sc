camera {
	pos(1,2,2)
	dir(3,2,1)
}

object {
	type(sphere)
	pos(1,-3, 4, 34)
	pos(0,-10,20)
	radius(10)
	color(174,106 ,160)
}

object {
	type(cylinder)
	pos(-10, 20 , 50)
	radius(5)
	color(146, 43, 125)
	rotation(45, 45)
}

object {
	type(cone)
	pos(50,0,120)
	angle(3)
	rotation(0,0)
	color(176, 32, 104)
}

object {
	type(plane)
	pos(70, 0,121)
	vector(3,0,0)
	color(254, 255, 149)
}

light {
	pos(12.2,21,4.3)
}
