#include <LiquidCrystal.h>
#include <util/delay.h>
#include <Arduino.h>

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


unsigned char menuPosition = 1;
uint8_t refreshLCD = 1;
uint16_t raw;
char buf[7];
int screenWidth = 16;
int screenHeight = 2;

// Quiz Questions and Answers
const char *questions[] = {
    "Capital of USA?",
    "Largest planet?",
    "Chem.symbol gold?",
    "Largest desert?",
    "Curency of Japan?",
    "Largest ocean?",
    "Biggest city EU?",
    "Year WW II ended?",
    "Moon landing year?",
    "Capital of Canada?",
    "known as RedPlanet?",
    "Sides a hexagon?"
};

const char *options[][2] = {
    {"-N.Y.C", "-D.C"},
    {"-Earth", "-Jupiter"},
    {"-Au", "-Ag"},
    {"Antarctica ", "-Sahara "},
    {"-Yen", "-Lira"},
    {"-Pacific", "-Atlantic"},
    {"-Istanbul", "-Rome"},
    {"-1945", "-1946"},
    {"-1969", "-1971"},
    {"-Ottawa", "-Toronto"},
    {"-Venus", "-Mars"},
    {"-8", "-6"}
};

char correctAnswers[] = {'b', 'b', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'b', 'b'};

int correctCount = 0;  // Variable to count correct answers

void checkAnswer(char userAnswer)
{
    lcd.setCursor(0, 1);
    if (userAnswer == correctAnswers[menuPosition - 1])
    {
      lcd.setCursor(0, 0);
      lcd.print(" Your answer is  ");
      lcd.setCursor(0, 1);
        lcd.print("    Correct!    ");
        correctCount++;
    }
    else
    {
       lcd.setCursor(0, 0);
      lcd.print(" Your answer is  ");
       lcd.setCursor(0, 1);
        lcd.print("     Wrong!     ");
      
    }
    _delay_ms(2000);
}
void start()
{
     lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Let's Start Quiz!");
    
    delay(3000);
}

void displayQuestion()
{
  if(menuPosition <= 1)
{
      start();
}
    lcd.clear();
    lcd.setCursor(0, 0);
    // Print the truncated question on the first line
    lcd.print(questions[menuPosition - 1]);

    // Print the truncated first option on the second line
    lcd.setCursor(0, 1);
    lcd.print(options[menuPosition - 1][0]);

    // Print the truncated second option on the second line, starting from column 8
    lcd.setCursor(8, 1);
    lcd.print(options[menuPosition - 1][1]);
}


void displayResult()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   Quiz Over!");
    lcd.setCursor(0, 1);
    lcd.print("True Answers: ");
    lcd.setCursor(13, 1);
    lcd.print(correctCount);
}
void displayPassed()
{
         lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" CONGRATULATIONS!");
    lcd.setCursor(0, 1);
    lcd.print("   YOU PASSED!");
}
void displayPassedNot()
{
         lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Could't pass!");
    lcd.setCursor(0, 1);
    lcd.print("    Try again!");
}
void setup()
{
    lcd.begin(screenWidth, screenHeight);
}

void loop()
{
    // MEASURE ADC
    raw = analogRead(A0);

    // UP
    if ((100 < raw) && (raw < 250) && (menuPosition > 1))
    {
        menuPosition--;
        refreshLCD = 1;
    }

    // DOWN
    if ((250 < raw) && (raw < 350) && (menuPosition < 12))
    {
        menuPosition++;
        refreshLCD = 1;
    }

    if (refreshLCD)
    {
        displayQuestion();
        refreshLCD = 0;
    }
      
  

    // RIGHT
    if ((raw >= 0) && (raw < 100) && (menuPosition < 14))
    {
        // Simulate selecting option 'a'
        checkAnswer('b');
        // Move to the next question or display result if the quiz is over
        
            menuPosition++;
            refreshLCD = 1;
             }
            if (menuPosition == 13)

{
  displayResult();
  refreshLCD = 1;
 
  if ((500 < raw) && (raw < 800) && (menuPosition <= 15))
    {
        
        refreshLCD = 1;
    
  if (correctCount>=8 )
   {
    displayPassed();
    refreshLCD = 1;
    delay(5000);
   }
   else
   {
    displayPassedNot();
    refreshLCD = 1;
     delay(5000);
   }
}      
}
           
  
    //LEFT
  if ((raw >350) && (raw < 500) && (menuPosition < 14))
    {
        // Simulate selecting option 'a'
        checkAnswer('a');
        // Move to the next question or display result if the quiz is over
        
            menuPosition++;
            refreshLCD = 1;
    }

 delay(100);
}
