package com.upf.abottomupsensortestbed43;

import java.util.ArrayList;

public class Properties {
	
	private ArrayList<String> tags;
	private String id;
	private String unit;
	private java.sql.Timestamp timeStamp;
	private String address;
	private String datasetName;
	private String description;
	private String datasetId;
	private String name;
	private float value;
	
	public Properties() {
		super();
	}
	
	public Properties(ArrayList<String> tags, String id, String unit,
			java.sql.Timestamp timeStamp, String address, String datasetName,
			String description, String datasetId, String name, float value) {
		super();
		this.tags = tags;
		this.id = id;
		this.unit = unit;
		this.timeStamp = timeStamp;
		this.address = address;
		this.datasetName = datasetName;
		this.description = description;
		this.datasetId = datasetId;
		this.name = name;
		this.value = value;
	}

	public ArrayList<String> getTags() {
		return tags;
	}

	public void setTags(ArrayList<String> tags) {
		this.tags = tags;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getUnit() {
		return unit;
	}

	public void setUnit(String unit) {
		this.unit = unit;
	}

	public java.sql.Timestamp getTimeStamp() {
		return timeStamp;
	}

	public void setTimeStamp(java.sql.Timestamp timeStamp) {
		this.timeStamp = timeStamp;
	}

	public String getAddress() {
		return address;
	}

	public void setAddress(String address) {
		this.address = address;
	}

	public String getDatasetName() {
		return datasetName;
	}

	public void setDatasetName(String datasetName) {
		this.datasetName = datasetName;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public String getDatasetId() {
		return datasetId;
	}

	public void setDatasetId(String datasetId) {
		this.datasetId = datasetId;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public float getValue() {
		return value;
	}

	public void setValue(float value) {
		this.value = value;
	}

	@Override
	public String toString() {
		return "Properties [tags=" + tags + ", id=" + id + ", unit=" + unit
				+ ", timeStamp=" + timeStamp + ", address=" + address
				+ ", datasetName=" + datasetName + ", description="
				+ description + ", datasetId=" + datasetId + ", name=" + name
				+ ", value=" + value + "]";
	}
	
	
	 
	

}
