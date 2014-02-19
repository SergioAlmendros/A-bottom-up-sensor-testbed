package com.upf.abottomupsensortestbed43;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Vector;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.SystemClock;
import android.util.Log;
import android.widget.Toast;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.MapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;
import com.json.parsers.JSONParser;
import com.json.parsers.JsonParserFactory;

public class MainActivity extends Activity {

	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		DataBase dataBase = DataBase.getInstance();
		
		// Get a handle to the Map Fragment
		dataBase.map = ((MapFragment) getFragmentManager().findFragmentById(
				R.id.map)).getMap();

		new HttpAsyncTask()
				.execute("http://opendata.nets.upf.edu/osn2/api/datasets/getDatasetJsonp/7b1611c3-c688-474b-bcab-6e4921bfb109/androidpruebas/1");

		LatLng sydney = new LatLng(-33.867, 151.206);
		//LatLng sydney = new LatLng(this.Lfeatures.get(0).getGeometry().getCoordinates().get(0), this.Lfeatures.get(0).getGeometry().getCoordinates().get(1));

		dataBase.map.setMyLocationEnabled(true);
		dataBase.map.moveCamera(CameraUpdateFactory.newLatLngZoom(sydney, 13));
		
		
		
		
	}

	public static String GET(String url) {
		InputStream inputStream = null;
		String result = "";
		try {

			// create HttpClient
			HttpClient httpclient = new DefaultHttpClient();

			// make GET request to the given URL
			HttpResponse httpResponse = httpclient.execute(new HttpGet(url));

			// receive response as inputStream
			inputStream = httpResponse.getEntity().getContent();

			// convert inputstream to string
			if (inputStream != null)
				result = convertInputStreamToString(inputStream);
			else
				result = "Did not work!";

		} catch (Exception e) {
			Log.d("InputStream", e.getLocalizedMessage());
		}

		return result;
	}

	private static String convertInputStreamToString(InputStream inputStream)
			throws IOException {
		BufferedReader bufferedReader = new BufferedReader(
				new InputStreamReader(inputStream));
		String line = "";
		String result = "";
		while ((line = bufferedReader.readLine()) != null)
			result += line;

		inputStream.close();
		return result;

	}

	private class HttpAsyncTask extends AsyncTask<String, Void, String> {
		@Override
		protected String doInBackground(String... urls) {

			return GET(urls[0]);
		}

		// onPostExecute displays the results of the AsyncTask.
		@Override
		protected void onPostExecute(String result) {
			Toast.makeText(getBaseContext(), "Received!", Toast.LENGTH_LONG)
					.show();
			// The JSON comes with the word callback which I don't want
			String nuevo = result.substring(9, result.length() - 1);
			JSONObject json;

			try {
				json = new JSONObject(nuevo);
				// etResponse.setText(json.toString(1));

				// JSONObject o = new JSONObject();

				JSONArray features = (JSONArray) json.get("features");

				List<String> listFeatures = new ArrayList<String>();

				for (int i = 0; i < features.length(); i++) {
					listFeatures.add(features.get(i).toString());
				}
				JsonParserFactory factory = JsonParserFactory.getInstance();
				JSONParser parser = factory.newJsonParser();
				Map jsonMap;
				HashMap propertiesHM, geometryHM;
				ArrayList tagsAL, coordinatesAL, tagsALp;
				Vector<Float> coordinatesV;

				Feature feature;
				Properties properties;
				Geometry geometry;
				
				DataBase dataBase = DataBase.getInstance();

				for (int i = 0; i < listFeatures.size(); i++) {

					jsonMap = parser.parseJson(listFeatures.get(i));

					propertiesHM = (HashMap) jsonMap.get("properties");
					geometryHM = (HashMap) jsonMap.get("geometry");
					tagsAL = (ArrayList) jsonMap.get("tags");
					coordinatesAL = (ArrayList) geometryHM.get("coordinates");

					String[] t = ((String) propertiesHM.get("tags")).split(",");

					tagsALp = new ArrayList<String>();

					for (int j = 0; j < t.length; j++) {
						tagsALp.add(t[j]);
					}

					properties = new Properties(
							tagsALp,
							(String) propertiesHM.get("id"),
							(String) propertiesHM.get("unit"),
							(String) propertiesHM.get("timeStamp"),
							(String) propertiesHM.get("address"),
							(String) propertiesHM.get("datasetName"),
							(String) propertiesHM.get("description"),
							(String) propertiesHM.get("datasetId"),
							(String) propertiesHM.get("name"),
							Float.parseFloat((String) propertiesHM.get("value")));

					coordinatesV = new Vector<Float>();

					for (int j = 0; j < coordinatesAL.size(); j++) {
						coordinatesV.add(Float
								.parseFloat((String) coordinatesAL.get(j)));
					}

					geometry = new Geometry((String) geometryHM.get("type"),
							coordinatesV);

					feature = new Feature(tagsAL, properties,
							(String) jsonMap.get("type"), geometry);
					
					
					
					dataBase.getLfeatures().add(feature);
					
				}
				Toast.makeText(getBaseContext(), "JSON parsed!",
						Toast.LENGTH_LONG).show();
				
				dataBase.setState("ready");
				dataBase.addMarker();

			} catch (JSONException e) {
				// etResponse.setText("Failed to extract the JSON: \n" + e);
				Toast.makeText(getBaseContext(),
						"There was a problem parsing the JSON!",
						Toast.LENGTH_LONG).show();
			}

		}
	}

}