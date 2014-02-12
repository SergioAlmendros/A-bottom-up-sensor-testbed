package com.example.a_bottom_up_sensor_testbed;

import java.util.List;

public class Feature {
	
	//Attributes: tags, properties, geometry.
	
	private List<String> tags;
	private Properties properties;
	private String type;
	private Geometry geometry;
	
	public Feature(List<String> tags, Properties properties, String type,
			Geometry geometry) {
		super();
		this.tags = tags;
		this.properties = properties;
		this.type = type;
		this.geometry = geometry;
	}

	public List<String> getTags() {
		return tags;
	}

	public void setTags(List<String> tags) {
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
