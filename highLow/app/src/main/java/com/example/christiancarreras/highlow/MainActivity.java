package com.example.christiancarreras.highlow;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;
import android.util.Log;

import java.util.*;

public class MainActivity extends AppCompatActivity {

    int randomNumber;
    Random randomGenerator = new Random();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        randomNumber = randomGenerator.nextInt(21);
        Log.d("Random Number: ", "" + randomNumber);
    }

    public void checkGuess(View view) {

        EditText guessedNumber  = (EditText) findViewById(R.id.guessedNumber);
        if(guessedNumber.getText().toString().matches("")) {
            Toast.makeText(getApplicationContext(), "You must enter a number between 0 and 20", Toast.LENGTH_LONG).show();
        }

        else {
            int guessedNumberInt = Integer.parseInt(guessedNumber.getText().toString());
            if(guessedNumberInt < 0 || guessedNumberInt > 20)
                Toast.makeText(getApplicationContext(), "Number Out Of Bounds", Toast.LENGTH_LONG).show();

            else {
                if (guessedNumberInt > randomNumber) {
                    Toast.makeText(getApplicationContext(), "Too High", Toast.LENGTH_LONG).show();
                } else if (guessedNumberInt < randomNumber) {
                    Toast.makeText(getApplicationContext(), "Too Low", Toast.LENGTH_LONG).show();
                } else {
                    Toast.makeText(getApplicationContext(), "You Got It! I'll Choose Another Number", Toast.LENGTH_LONG).show();
                    randomize(view);
                }
            }
        }
    }

    public void randomize(View view) {
        randomNumber = randomGenerator.nextInt(21);
        Log.d("Random Number: ", "" + randomNumber);
        Toast.makeText(getApplicationContext(), "I'm Thinking Of A New Number", Toast.LENGTH_LONG).show();
    }
}
