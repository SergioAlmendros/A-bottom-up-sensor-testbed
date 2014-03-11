package com.upf.abottomupsensortestbed43;

import java.util.Vector;

public class Geometry {
	
	private String type;
	private Vector<Float> coordinates;
	
	public Geometry() {
		super();
	}
	
	public Geometry(String type, Vector<Float> coordinates) {
		super();
		this.type = type;
		this.coordinates = coordinates;
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	public Vector<Float> getCoordinates() {
		return coordinates;
	}

	public void setCoordinates(Vector<Float> coordinates) {
		this.coordinates = coordinates;
	}

	@Override
	public String toString() {
		return "Geometry [type=" + type + ", coordinates=" + coordinates + "]";
	}
	
	

}