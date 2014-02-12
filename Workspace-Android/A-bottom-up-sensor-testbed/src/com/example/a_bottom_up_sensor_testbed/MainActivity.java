package com.example.a_bottom_up_sensor_testbed;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONException;
import org.json.JSONObject;
import org.json.JSONArray;

import com.json.parsers.JSONParser;
import com.json.parsers.JsonParserFactory;

import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import android.app.Activity;
 
public class MainActivity extends Activity {
 
    EditText etResponse;
    TextView tvIsConnected;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
 
        // get reference to the views
        etResponse = (EditText) findViewById(R.id.etResponse);
        tvIsConnected = (TextView) findViewById(R.id.tvIsConnected);
 
        // check if you are connected or not
        if(isConnected()){
            tvIsConnected.setBackgroundColor(0xFF00CC00);
            tvIsConnected.setText("You are connected");
        }
        else{
            tvIsConnected.setText("You are NOT connected");
        }
 
        // call AsynTask to perform network operation on separate thread
        new HttpAsyncTask().execute("http://opendata.nets.upf.edu/osn2/api/datasets/getDatasetJsonp/7b1611c3-c688-474b-bcab-6e4921bfb109/androidpruebas/1");
    }
 
    public static String GET(String url){
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
            if(inputStream != null)
                result = convertInputStreamToString(inputStream);
            else
                result = "Did not work!";
 
        } catch (Exception e) {
            Log.d("InputStream", e.getLocalizedMessage());
        }
 
        return result;
    }
 
    private static String convertInputStreamToString(InputStream inputStream) throws IOException{
        BufferedReader bufferedReader = new BufferedReader( new InputStreamReader(inputStream));
        String line = "";
        String result = "";
        while((line = bufferedReader.readLine()) != null)
            result += line;
 
        inputStream.close();
        return result;
 
    }
 
    public boolean isConnected(){
        ConnectivityManager connMgr = (ConnectivityManager) getSystemService(Activity.CONNECTIVITY_SERVICE);
            NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();
            if (networkInfo != null && networkInfo.isConnected()) 
                return true;
            else
                return false;   
    }
    private class HttpAsyncTask extends AsyncTask<String, Void, String> {
        @Override
        protected String doInBackground(String... urls) {
 
            return GET(urls[0]);
        }
        // onPostExecute displays the results of the AsyncTask.
        @Override
        protected void onPostExecute(String result) {
            Toast.makeText(getBaseContext(), "Received!", Toast.LENGTH_LONG).show();
            //The JSON comes with the word callback which I don't want
            String nuevo = result.substring(9, result.length()-1); 
            JSONObject json;
            
			try {
				json = new JSONObject(nuevo);
				//etResponse.setText(json.toString(1));
				
				//JSONObject o = new JSONObject();
				
				JSONArray features = (JSONArray) json.get("features");
				
				List<String> listFeatures = new ArrayList<String>();
				
				for(int i=0; i<features.length(); i++){
					listFeatures.add(features.get(i).toString());
				}
				JsonParserFactory factory = JsonParserFactory.getInstance();
				JSONParser parser=factory.newJsonParser();
				Map jsonMap;
				
				
				Feature feature;
				Properties properties;
				Geometry geometry;
				
				for(int i=0; i<listFeatures.size(); i++){
					
					jsonMap = parser.parseJson(listFeatures.get(i));
					
					//etResponse.setText(jsonMap.keySet().toString());
					//etResponse.append("\n" + jsonMap.get("properties").toString());
					
					HashMap propertiesHM = (HashMap)jsonMap.get("properties");
					
					etResponse.append("\n" + propertiesHM.keySet().toString());
					etResponse.append("\n" + propertiesHM.get("tags").getClass().toString());
					
					/*etResponse.setText(tagsMap.keySet().toString()+"\n");
					etResponse.append(propertiesMap.keySet().toString()+"\n");
					etResponse.append(geometryMap.keySet().toString());*/
					
					
					
					break;
				}
				
				
				
				

				//De esta forma consigo los diferentes features.
				//etResponse.append( arrayOfFeatures.get(1).toString() );
				
				
				
			} catch (JSONException e) {
				etResponse.setText("Failed to extract the JSON: \n" + e);
			}
          
       }
    }
}