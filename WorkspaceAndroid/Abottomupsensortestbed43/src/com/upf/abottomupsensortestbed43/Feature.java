package com.upf.abottomupsensortestbed43;


import java.util.ArrayList;

public class Feature {
	
	//Attributes: tags, properties, geometry.
	
	private ArrayList<String> tags;
	private Properties properties;
	private String type;
	private Geometry geometry;
	
	public Feature() {
		super();
	}

	public Feature(ArrayList<String> tags, Properties properties, String type,
			Geometry geometry) {
		super();
		this.tags = tags;
		this.properties = properties;
		this.type = type;
		this.geometry = geometry;
	}

	public ArrayList<String> getTags() {
		return tags;
	}

	public void setTags(ArrayList<String> tags) {
		this.tags = tags;
	}

	public Properties getProperties() {
		return properties;
	}

	public void setProperties(Properties properties) {
		this.properties = properties;
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	public Geometry getGeometry() {
		return geometry;
	}

	public void setGeometry(Geometry geometry) {
		this.geometry = geometry;
	}

	@Override
	public String toString() {
		return "Feature [tags=" + tags + ", properties=" + properties
				+ ", type=" + type + ", geometry=" + geometry + "]";
	}
	
	

}