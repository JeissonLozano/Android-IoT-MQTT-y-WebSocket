package com.mqtt.appguia5;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import pl.pawelkleczkowski.customgauge.CustomGauge;

public class MainActivity extends AppCompatActivity {
    // Variables Globales
    MqttAndroidClient client;
    //Card1
    Switch SwitchLed1;
    String estadoSwitch1;
    Switch SwitchLed2;
    String estadoSwitch2;
    // Card 2 y 3
    CustomGauge gaugeA;
    TextView textGagueA;

    CustomGauge gaugeB;
    TextView textGagueB;

    // Card 4
    EditText editText;
    String payload;
    Button btnEnviar;

    // Card 5
    TextView textTemp;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //Inicio Card1
        SwitchLed1 = (Switch) findViewById(R.id.Led1);
        SwitchLed2 = (Switch) findViewById(R.id.Led2);

        SwitchLed1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(SwitchLed1.isChecked()){
                    try{
                        MqttMessage message = new MqttMessage(("ON").getBytes());
                        client.publish("IoT/Led1", message);
                    } catch (MqttException e){
                        e.printStackTrace();
                    }
                } else{
                    try{
                        MqttMessage message = new MqttMessage(("OFF").getBytes());
                        client.publish("IoT/Led1", message);
                    } catch (MqttException e){
                        e.printStackTrace();
                    }
                }
            }
        });

        SwitchLed2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(SwitchLed2.isChecked()){
                    try{
                        MqttMessage message = new MqttMessage(("ON").getBytes());
                        client.publish("IoT/Led2", message);
                    } catch (MqttException e){
                        e.printStackTrace();
                    }
                } else{
                    try{
                        MqttMessage message = new MqttMessage(("OFF").getBytes());
                        client.publish("IoT/Led2", message);
                    } catch (MqttException e){
                        e.printStackTrace();
                    }
                }
            }
        });



        //Fin Card1

        //Inicio Card 2 y 3

        gaugeA= (CustomGauge) findViewById(R.id.gauge1);
        textGagueA = (TextView) findViewById(R.id.valueGauge1);

        gaugeB= (CustomGauge) findViewById(R.id.gauge2);
        textGagueB = (TextView) findViewById(R.id.valueGauge2);

        //Fin Card 2 y 3

        // Inicio Card 4

        editText = (EditText) findViewById(R.id.editarTexto);
        btnEnviar = (Button) findViewById(R.id.enviarTexto);

        btnEnviar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String topic = "IoT/Text";
                payload = editText.getText().toString();

                try{
                    client.publish(topic, payload.getBytes(), 0 , false);
                } catch (MqttException e){
                    e.printStackTrace();
                }


            }
        });

        // Fin Card 4

        // Card 5

        textTemp = (TextView) findViewById(R.id.textTemp);



        String clientId = MqttClient.generateClientId();
         client =
                new MqttAndroidClient(this.getApplicationContext(), "tcp://100.25.254.82:1883",
                        clientId);

        try {
            IMqttToken token = client.connect();
            token.setActionCallback(new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken) {
                    // Si mqtt conectó
                    Toast.makeText(MainActivity.this, "CONECTADO MQTT", Toast.LENGTH_LONG).show();
                    suscripcionTopics();
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                    // Something went wrong e.g. connection timeout or firewall problems
                    Toast.makeText(MainActivity.this, "ERROR DE CONEXIÓN", Toast.LENGTH_LONG).show();

                }
            });
        } catch (MqttException e) {
            e.printStackTrace();
        }

        // Parte del callback

        client.setCallback(new MqttCallback() {
            @Override
            public void connectionLost(Throwable cause) {

            }

            @Override
            public void messageArrived(String topic, MqttMessage message) throws Exception {
                //Aqui cuando los mensajes lleguen.
                //Card 1

                if(topic.matches("IoT/Led1")){
                    estadoSwitch1 = new String(message.getPayload());

                    if(estadoSwitch1.matches("ON")){
                        SwitchLed1.setChecked(true);
                    }else{
                        SwitchLed1.setChecked(false);
                    }
                }

                if(topic.matches("IoT/Led2")){
                    estadoSwitch2 = new String(message.getPayload());

                    if(estadoSwitch2.matches("ON")){
                        SwitchLed2.setChecked(true);
                    }else{
                        SwitchLed2.setChecked(false);
                    }
                }

                //Card 2 y 3

                if(topic.matches("IoT/Pot1")){
                    gaugeA.setValue(Integer.parseInt(new String(message.getPayload())));
                    textGagueA.setText(new String(message.getPayload()));
                }

                if(topic.matches("IoT/Pot2")){
                    gaugeB.setValue(Integer.parseInt(new String(message.getPayload())));
                    textGagueB.setText(new String(message.getPayload()));
                }


                // Card 5

                if(topic.matches("IoT/Temp")){
                    textTemp.setText(new String(message.getPayload()));
                }


            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken token) {

            }
        });



    }

    private void suscripcionTopics(){

        try{
            client.subscribe("IoT/Pot1",0);
            client.subscribe("IoT/Pot2",0);
            client.subscribe("IoT/Temp",0);
            client.subscribe("IoT/Led1",0);
            client.subscribe("IoT/Led2",0);

        }catch (MqttException e){
            e.printStackTrace();
        }

    }

}
