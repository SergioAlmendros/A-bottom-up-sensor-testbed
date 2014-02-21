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
	private String DATASETID = "temperature";
	private String APIKEY = "7b1611c3-c688-474b-bcab-6e4921bfb109";

	public String getDATASETID() {
		return DATASETID;
	}

	public void setDATASETID(String dATASETID) {
		DATASETID = dATASETID;
	}

	public String getAPIKEY() {
		return APIKEY;
	}

	public void setAPIKEY(String aPIKEY) {
		APIKEY = aPIKEY;
	}

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
		// for (int i = 0; i < this.Lfeatures.size(); ++i) {
		//
		// place = new LatLng((float)this.Lfeatures.get(i).getGeometry()
		// .getCoordinates().get(1), (float)this.Lfeatures.get(i)
		// .getGeometry().getCoordinates().get(0));
		// this.map.addMarker(new MarkerOptions()
		// .title(this.Lfeatures.get(i).getProperties().getId())
		// .snippet(
		// ""
		// + this.Lfeatures.get(i).getProperties()
		// .getDescription()
		// + "\n"
		// + this.Lfeatures.get(i).getProperties()
		// .getValue()).position(place));
		// }

		// Tiene que encontrar la ultima feature (ej: id = 1.47.1 + 1.47.2 +
		// 1.47.3 + 1.47.4 con el timestamp mas grande

		// Buscar el timestamp mas grande, una vez hecho esto, coger las
		// features con id parecida

		Feature f_maxTimeStamp;

		if (this.Lfeatures.size() > 0) {
			f_maxTimeStamp = this.Lfeatures.get(0);
			for (int i = 1; i < this.Lfeatures.size(); ++i) {

				if (!f_maxTimeStamp
						.getProperties()
						.getTimeStamp()
						.after(this.Lfeatures.get(i).getProperties()
								.getTimeStamp())) {
					f_maxTimeStamp = this.Lfeatures.get(i);
				}

			}
		}
		
		ArrayList<Feature> Markerfeatures = new ArrayList<Feature>();
		
		for(int i=0; i<this.Lfeatures.size(); ++i){
			
		}

	}
}


















