camera {
	pos(0, 0, 0)
	dir(0, 0, 1)
}

object {
	type(sphere)
	pos(0, 0, 100)
	radius(10)
	color(255, 255, 255)
}

object {
	type(sphere)
	pos(30, -30, 100)
	radius(10)
	color(255, 255, 255)
}

object {
	type(sphere)
	pos(-30, 30, 100)
	radius(10)
	color(255, 255, 255)
}

object {
	type(plane)
	pos(-50, -50, 0)
	vector(1, 1, 0.2)
}

object {
	type(plane)
	pos(50, 50, 0)
	vector(1, 1, -0.2)
}
