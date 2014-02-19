package com.upf.abottomupsensortestbed43;

import java.util.ArrayList;

import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

public class DataBase {
    private static DataBase mInstance = null;

    private ArrayList<Feature> Lfeatures;
    private String state = "busy";
    GoogleMap map;

    private DataBase(){
        this.Lfeatures  = new ArrayList<Feature>();
    }

    public static DataBase getInstance(){
        if(mInstance == null)
        {
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
	
	public void addMarker(){
		LatLng sydney = new LatLng(-33.867, 151.206);
		this.map.addMarker(new MarkerOptions().title("Sydney")
				.snippet("" + this.Lfeatures.size())
				.position(sydney));
	}
	
	

    
}
