package com.upf.abottomupsensortestbed43;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map.Entry;
import java.util.StringTokenizer;

import android.graphics.Color;
import android.graphics.drawable.GradientDrawable;
import android.widget.Button;
import android.widget.TextView;

import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.TileOverlayOptions;
import com.google.maps.android.heatmaps.HeatmapTileProvider;
import com.google.maps.android.heatmaps.WeightedLatLng;

public class DataBase {
	private static DataBase mInstance = null;

	private ArrayList<Feature> Lfeatures;
	private String state = "busy";
	GoogleMap map;
	LatLng currentLocation;
	TextView textView;
	Button bTemp, bHum, bNoise, blight, bG, bM;
	private String DATASETID = "environmental";
	private String APIKEY = "7b1611c3-c688-474b-bcab-6e4921bfb109";
	private HashMap<String, LinkedList<Feature>> featuresByCoordinates = new HashMap<String, LinkedList<Feature>>();
	private ArrayList<WeightedLatLng> heatmaplistTemp = new ArrayList<WeightedLatLng>();
	private ArrayList<WeightedLatLng> heatmaplistHum = new ArrayList<WeightedLatLng>();
	private ArrayList<WeightedLatLng> heatmaplistNoise = new ArrayList<WeightedLatLng>();
	private ArrayList<WeightedLatLng> heatmaplistlight = new ArrayList<WeightedLatLng>();
	private ArrayList<WeightedLatLng> heatmaplistG = new ArrayList<WeightedLatLng>();
	private ArrayList<Feature> lfeaturesMarkersT = new ArrayList<Feature>();
	private ArrayList<Feature> lfeaturesMarkersH = new ArrayList<Feature>();
	private ArrayList<Feature> lfeaturesMarkersN = new ArrayList<Feature>();
	private ArrayList<Feature> lfeaturesMarkersL = new ArrayList<Feature>();
	private ArrayList<Feature> lfeaturesMarkersG = new ArrayList<Feature>();
	GradientDrawable dselected, dunselected;
	boolean markerSelected = false;
	String bSelected = "Temperature";

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

			mInstance.dselected = new GradientDrawable();
			mInstance.dselected.setShape(GradientDrawable.RECTANGLE);
			mInstance.dselected.setStroke(5, Color.argb(0, 0, 0, 0));
			mInstance.dselected.setColor(Color.argb(125, 0, 125, 0));
			// dataBase.bTemp.setBackground(dselected);

			mInstance.dunselected = new GradientDrawable();
			mInstance.dunselected.setShape(GradientDrawable.RECTANGLE);
			mInstance.dunselected.setStroke(5, Color.argb(0, 0, 0, 0));
			mInstance.dunselected.setColor(Color.argb(125, 0, 0, 0));
			// dataBase.bTemp.setBackground(dunselected);

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

	public void fillLists() {

		LatLng place;

		Feature f_maxTimeStamp = null;
		StringTokenizer keys;
		LinkedList<Feature> lf;
		LinkedList<Feature> lfmt = new LinkedList<Feature>();

		for (Entry<String, LinkedList<Feature>> entry : this.featuresByCoordinates
				.entrySet()) {
			lf = entry.getValue();

			f_maxTimeStamp = lf.get(0);
			for (int j = 1; j < lf.size(); ++j) {

				if (!f_maxTimeStamp.getProperties().getTimeStamp()
						.after(lf.get(j).getProperties().getTimeStamp())) {
					f_maxTimeStamp = lf.get(j);
				}
			}
			lfmt.add(f_maxTimeStamp);

		}

		ArrayList<Feature> Markerfeatures = new ArrayList<Feature>();

		// Parsear la id: 1.47.2:
		// 1: ID arduino
		// 47: ID del upload de las 4 features
		// 2: Tipo de datos (Temperatura, ruido,...)
		String one, two, three;
		StringTokenizer split;

		for (int i = 0; i < lfmt.size(); i++) {
			lf = this.featuresByCoordinates.get(lfmt.get(i).getGeometry()
					.getCoordinates().get(0)
					+ "-" + lfmt.get(i).getGeometry().getCoordinates().get(1));

			split = new StringTokenizer(lfmt.get(i).getProperties().getId(),
					".");

			if (split.countTokens() == 3) {
				one = split.nextToken();
				two = split.nextToken();
				three = split.nextToken();
				if (one.matches("-?\\d+") && two.matches("-?\\d+")
						&& three.matches("-?\\d+")) {

					String id = one + "." + two;
					String id2;

					for (int j = 0; j < lf.size(); ++j) {
						id2 = lf.get(j).getProperties().getId();
						if (id2.equals(id + "." + "1")
								|| id2.equals(id + "." + "2")
								|| id2.equals(id + "." + "3")
								|| id2.equals(id + "." + "4")
								|| id2.equals(id + "." + "5")) {

							Markerfeatures.add(lf.get(j));

						}
					}
				}
			}

		}

		for (int i = 0; i < Markerfeatures.size(); ++i) {

			place = new LatLng((float) Markerfeatures.get(i).getGeometry()
					.getCoordinates().get(1), (float) Markerfeatures.get(i)
					.getGeometry().getCoordinates().get(0));

			if (Markerfeatures.get(i).getProperties().getDescription()
					.contains("Temperature")) {

				addWeightedLatLng(place, Markerfeatures.get(i).getProperties()
						.getValue(), "Temperature");
				this.lfeaturesMarkersT.add(Markerfeatures.get(i));

			} else if (Markerfeatures.get(i).getProperties().getDescription()
					.contains("Light")) {

				addWeightedLatLng(place, Markerfeatures.get(i).getProperties()
						.getValue(), "Light");
				this.lfeaturesMarkersL.add(Markerfeatures.get(i));

			} else if (Markerfeatures.get(i).getProperties().getDescription()
					.contains("Noise")) {

				addWeightedLatLng(place, Markerfeatures.get(i).getProperties()
						.getValue(), "Noise");
				this.lfeaturesMarkersN.add(Markerfeatures.get(i));

			} else if (Markerfeatures.get(i).getProperties().getDescription()
					.contains("Humidity")) {

				addWeightedLatLng(place, Markerfeatures.get(i).getProperties()
						.getValue(), "Humidity");
				this.lfeaturesMarkersH.add(Markerfeatures.get(i));

			} else if (Markerfeatures.get(i).getProperties().getDescription()
					.contains("Gas")) {

				addWeightedLatLng(place, Markerfeatures.get(i).getProperties()
						.getValue(), "Gas");
				this.lfeaturesMarkersG.add(Markerfeatures.get(i));

			}
		}

	}

	private void addWeightedLatLng(LatLng place, float value, String type) {

		float sum = (float) 0.00001;
		float sum2 = (float) 0.000008;
		LatLng nplace;
		ArrayList<WeightedLatLng> heatmaplist = new ArrayList<WeightedLatLng>();

		if (type.equals("Temperature")) {
			heatmaplist = this.heatmaplistTemp;
		} else if (type.equals("Light")) {
			heatmaplist = this.heatmaplistlight;
		} else if (type.equals("Noise")) {
			heatmaplist = this.heatmaplistNoise;
		} else if (type.equals("Humidity")) {
			heatmaplist = this.heatmaplistHum;
		} else if (type.equals("Gas")) {
			heatmaplist = this.heatmaplistG;
		}

		heatmaplist.add(new WeightedLatLng(place, value));

		nplace = new LatLng((float) place.latitude + sum,
				(float) place.longitude);
		heatmaplist.add(new WeightedLatLng(nplace, value));

		nplace = new LatLng((float) place.latitude, (float) place.longitude
				+ sum);
		heatmaplist.add(new WeightedLatLng(nplace, value));

		nplace = new LatLng((float) place.latitude - sum,
				(float) place.longitude);
		heatmaplist.add(new WeightedLatLng(nplace, value));

		nplace = new LatLng((float) place.latitude, (float) place.longitude
				- sum);
		heatmaplist.add(new WeightedLatLng(nplace, value));

		nplace = new LatLng((float) place.latitude + sum2,
				(float) place.longitude + sum2);
		heatmaplist.add(new WeightedLatLng(nplace, value));

		nplace = new LatLng((float) place.latitude + sum2,
				(float) place.longitude - sum2);
		heatmaplist.add(new WeightedLatLng(nplace, value));

		nplace = new LatLng((float) place.latitude - sum2,
				(float) place.longitude + sum2);
		heatmaplist.add(new WeightedLatLng(nplace, value));

		nplace = new LatLng((float) place.latitude - sum2,
				(float) place.longitude - sum2);
		heatmaplist.add(new WeightedLatLng(nplace, value));

	}

	public void createFeaturesByCoordinates() {

		String coordinates;

		for (int i = 0; i < this.Lfeatures.size(); ++i) {

			coordinates = Float.toString(this.Lfeatures.get(i).getGeometry()
					.getCoordinates().get(0))
					+ "-"
					+ Float.toString(this.Lfeatures.get(i).getGeometry()
							.getCoordinates().get(1));

			if (this.featuresByCoordinates.containsKey(coordinates) == false) {
				this.featuresByCoordinates.put(coordinates,
						new LinkedList<Feature>());
				this.featuresByCoordinates.get(coordinates).add(
						this.Lfeatures.get(i));

				// this.textView.setText("entra");

			} else {
				this.featuresByCoordinates.get(coordinates).add(
						this.Lfeatures.get(i));

				// this.textView.setText("entra");
			}
		}
		// this.textView.setText("entra " + this.featuresByCoordinates.size());

	}

	public void addMarkers(String type) {

		ArrayList<Feature> heatmaplist = new ArrayList<Feature>();
		if (type.equals("Temperature")) {
			heatmaplist = this.lfeaturesMarkersT;
		} else if (type.equals("Light")) {
			heatmaplist = this.lfeaturesMarkersL;
		} else if (type.equals("Noise")) {
			heatmaplist = this.lfeaturesMarkersN;
		} else if (type.equals("Humidity")) {
			heatmaplist = this.lfeaturesMarkersH;
		} else if (type.equals("Air Quality")) {
			heatmaplist = this.lfeaturesMarkersG;
		}

		for (int i = 0; i < heatmaplist.size(); ++i) {
			this.map.addMarker(new MarkerOptions().position(
					new LatLng((float) heatmaplist.get(i).getGeometry()
							.getCoordinates().get(1), (float) heatmaplist
							.get(i).getGeometry().getCoordinates().get(0)))
					.title(heatmaplist.get(i).getProperties().getValue()
							+ heatmaplist.get(i).getProperties().getUnit()));
		}
	}

	public void addHeatMaps(String type) {

		ArrayList<WeightedLatLng> heatmaplist = new ArrayList<WeightedLatLng>();

		if (type.equals("Temperature")) {
			heatmaplist = this.heatmaplistTemp;
		} else if (type.equals("Light")) {
			heatmaplist = this.heatmaplistlight;
		} else if (type.equals("Noise")) {
			heatmaplist = this.heatmaplistNoise;
		} else if (type.equals("Humidity")) {
			heatmaplist = this.heatmaplistHum;
		} else if (type.equals("Air Quality")) {
			heatmaplist = this.heatmaplistG;
		}

		if (!heatmaplist.isEmpty()) {

			HeatmapTileProvider mProvider = null;
			try {
				mProvider = new HeatmapTileProvider.Builder().weightedData(
						heatmaplist).build();
			} catch (Exception e) {
				this.textView.setText(e.toString());
			}
			// mProvider.setRadius(50);

			// this.textView.setText( mProvider.getmData().toString() );

			try {
				// Add a tile overlay to the map, using the heat map tile
				// provider.
				this.map.addTileOverlay(new TileOverlayOptions()
						.tileProvider(mProvider));
				// this.map.clear();
			} catch (Exception e) {
				this.textView.setText(e.toString());
			}
		}
	}
}

















