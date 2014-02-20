package com.upf.abottomupsensortestbed43;

import java.util.ArrayList;

import android.widget.EditText;

import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

public class DataBase {
	private static DataBase mInstance = null;

	private ArrayList<Feature> Lfeatures;
	private String state = "busy";
	GoogleMap map;
	LatLng currentLocation;
	EditText e;

	private DataBase() {
		this.Lfeatures = new ArrayList<Feature>();
	}

	public static DataBase getInstance() {
		if (mInstance == null) {
			mInstance = new DataBase();
		}
		return mInstance;
	}

	public ArrayList<Feature> getLfeatures() {
		return Lfeatures;
	}

	public void setLfeatures(ArrayList<Feature> lfeatures) {
		Lfeatures = lfeatures;
	}

	public String getState() {
		return state;
	}

	public void setState(String state) {
		this.state = state;
	}

	@Override
	public String toString() {
		return "DataBase [Lfeatures=" + Lfeatures + ", state=" + state + "]";
	}

	public void addMarkers() {

		LatLng place;
		for (int i = 0; i < this.Lfeatures.size(); ++i) {

			place = new LatLng((float)this.Lfeatures.get(i).getGeometry()
					.getCoordinates().get(1), (float)this.Lfeatures.get(i)
					.getGeometry().getCoordinates().get(0));
			this.map.addMarker(new MarkerOptions()
					.title(this.Lfeatures.get(i).getProperties().getId())
					.snippet(
							""
									+ this.Lfeatures.get(i).getProperties()
											.getDescription()
									+ " "
									+ this.Lfeatures.get(i).getProperties()
											.getValue()).position(place));
		}
		place = new LatLng(this.Lfeatures.get(0).getGeometry()
				.getCoordinates().get(1), this.Lfeatures.get(0)
				.getGeometry().getCoordinates().get(0));
		
		
		//this.map.setMyLocationEnabled(true);
		//this.map.moveCamera(CameraUpdateFactory.newLatLngZoom( place, 13));
	}

}


















