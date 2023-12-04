#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store activity information
typedef struct {
  char name[50];
  char description[200];
} Activity;

// Structure to store user information
typedef struct {
  char firstName[50];
  char lastName[50];
  char mood[20];
  Activity *activity;
} User;

// Function to create a new activity
Activity *createActivity(const char *name, const char *description) {
  Activity *newActivity = (Activity *)malloc(sizeof(Activity));
  strcpy(newActivity->name, name);
  strcpy(newActivity->description, description);
  return newActivity;
}

// Function to display activity information
void displayActivity(const Activity *activity) {
  printf("Activity: %s\nDescription: %s\n", activity->name,
         activity->description);
}

// Function to display user information
void displayUser(const User *user) {
  printf("\nUser Information:\n");
  printf("Name: %s %s\n", user->firstName, user->lastName);
  printf("Mood: %s\n", user->mood);
  if (user->activity != NULL) {
    displayActivity(user->activity);
  }
  printf("\n");
}

// Function to prompt user for name
void getUserName(User *user) {
  printf("Enter your first name: ");
  scanf("%s", user->firstName);
  printf("Enter your last name: ");
  scanf("%s", user->lastName);
}

// Function to prompt user for mood
void getUserMood(User *user) {
  printf("How are you feeling today?\n");
  printf("a. Happy\nb. Stressed\nc. Bored\n");
  printf("Choose an option (a, b, c): ");

  char choice;
  scanf(" %c", &choice);

  switch (choice) {
  case 'a':
    strcpy(user->mood, "Happy mood");
    break;
  case 'b':
    strcpy(user->mood, "Stressed mood");
    break;
  case 'c':
    strcpy(user->mood, "Bored mood");
    break;
  default:
    printf("Invalid choice! Defaulting to Neutral mood.\n");
    strcpy(user->mood, "Neutral mood");
  }
}

// Function to prompt user for activity type and return the appropriate library
Activity *getActivityLibrary(char choice) {
  int numActivitiesPerType = 3; // Number of activities per type

  switch (choice) {
  case 'a': {
    Activity *relaxationLibrary =
        (Activity *)malloc(numActivitiesPerType * sizeof(Activity));
    relaxationLibrary[0] = *createActivity(
        "Meditation", "Try a short meditation session. Find a quiet place, sit "
                      "comfortably, and focus on your breath.");
    relaxationLibrary[1] = *createActivity(
        "Soothing Bath",
        "Take a soothing bath with calming scents and gentle music.");
    relaxationLibrary[2] = *createActivity(
        "Deep Breathing",
        "Practice deep breathing exercises to calm your mind and body.");
    return relaxationLibrary;
  }
  case 'b': {
    Activity *entertainmentLibrary =
        (Activity *)malloc(numActivitiesPerType * sizeof(Activity));
    entertainmentLibrary[0] = *createActivity(
        "Favorite Show",
        "Watch a favorite TV show or movie to lift your spirits!");
    entertainmentLibrary[1] = *createActivity(
        "Music Time", "Listen to your favorite music or explore new genres for "
                      "a pleasant experience.");
    entertainmentLibrary[2] = *createActivity(
        "Crossword Puzzle", "Engage in a crossword puzzle or play a simple "
                            "game to keep your mind active.");
    return entertainmentLibrary;
  }
  case 'c': {
    Activity *productivityLibrary =
        (Activity *)malloc(numActivitiesPerType * sizeof(Activity));
    productivityLibrary[0] = *createActivity(
        "Journaling", "Write down your thoughts in a journal. It's a great way "
                      "to organize your ideas.");
    productivityLibrary[1] = *createActivity(
        "Home Organization", "Organize a small area of your home. Decluttering "
                             "can be a rewarding activity.");
    productivityLibrary[2] = *createActivity(
        "Set Goals",
        "Set small goals for the day and work towards achieving them.");
    return productivityLibrary;
  }
  default:
    printf("Invalid choice! Defaulting to Relaxation activities.\n");
    Activity *defaultLibrary =
        (Activity *)malloc(numActivitiesPerType * sizeof(Activity));
    defaultLibrary[0] = *createActivity(
        "Meditation", "Try a short meditation session. Find a quiet place, sit "
                      "comfortably, and focus on your breath.");
    defaultLibrary[1] = *createActivity(
        "Soothing Bath",
        "Take a soothing bath with calming scents and gentle music.");
    defaultLibrary[2] = *createActivity(
        "Deep Breathing",
        "Practice deep breathing exercises to calm your mind and body.");
    return defaultLibrary;
  }
}

// Function to prompt user for activity type
void getUserActivityType(User *user) {
  printf("What type of activity are you in the mood for?\n");
  printf("a. Relaxation\nb. Entertainment\nc. Productivity\n");
  printf("Choose an option (a, b, c): ");

  char choice;
  scanf(" %c", &choice);

  Activity *activityLibrary = getActivityLibrary(choice);

  // Display activities for the chosen type
  printf("\nActivities for %s:\n", activityLibrary[0].name);
  for (int i = 0; i < 3; i++) {
    printf("%d. %s\n", i + 1, activityLibrary[i].name);
  }

  // Prompt user to choose a specific activity
  int activityChoice;
  printf("Choose an activity (1-3): ");
  scanf("%d", &activityChoice);

  if (activityChoice >= 1 && activityChoice <= 3) {
    user->activity = &activityLibrary[activityChoice - 1];
  } else {
    printf("Invalid choice! No specific activity selected.\n");
  }

  // Free allocated memory for activity library
  free(activityLibrary);
}

// Function to handle post-activity mood check and physical discomfort inquiry
void postActivityMoodCheck(User *user) {
  printf("\nAfter completing the activity, let's check your mood again:\n");
  getUserMood(user);

  // Check if mood is stressed or neutral
  if (strcmp(user->mood, "Stressed mood") == 0 ||
      strcmp(user->mood, "Neutral mood") == 0) {
    printf("\nIt seems like you're feeling %s. Is there anything physically "
           "bothering you?\n",
           user->mood);

    char response;
    printf("Enter 'Y' for yes or 'N' for no: ");
    scanf(" %c", &response);

    if (response == 'Y' || response == 'y') {
      printf("Is it something serious or just a minor discomfort?\n");
      printf("Enter 'S' for serious or 'M' for minor: ");
      scanf(" %c", &response);

      if (response == 'S' || response == 's') {
        printf("Considering the seriousness of your discomfort, we recommend "
               "reaching out to emergency services.\n");
        // You may want to include instructions on how to contact emergency
        // services based on the platform.
      } else if (response == 'M' || response == 'm') {
        printf("Let's identify the area where you are feeling discomfort:\n");
        printf("a. Back\nb. Hands\nc. Legs\nd. Feet\ne. Neck\n");
        printf("Choose an option (a, b, c, d, e): ");

        scanf(" %c", &response);

        switch (response) {
        case 'a':
          printf("\nFor relieving tension in the back, try the following "
                 "stretching exercise:\n");
          printf("Stand up straight, interlace your fingers, and stretch your "
                 "arms forward. "
                 "Feel the stretch in your upper back. Hold for 15 seconds and "
                 "repeat.\n");
          break;
        case 'b':
          printf("\nTo relieve tension in your hands, try this exercise:\n");
          printf("Gently stretch your fingers and thumb outward, then make a "
                 "fist. "
                 "Repeat this movement several times to improve flexibility "
                 "and reduce stiffness.\n");
          break;
        case 'c':
          printf("\nFor your legs, here's a simple stretching exercise:\n");
          printf("Sit on the floor, extend one leg outward, and gently reach "
                 "toward your toes. "
                 "Hold for 15 seconds and switch legs. This helps stretch your "
                 "hamstrings.\n");
          break;
        case 'd':
          printf(
              "\nTo relieve tension in your feet, consider this exercise:\n");
          printf("Sit in a chair, lift one foot, and rotate your ankle in both "
                 "directions. "
                 "This can help improve circulation and reduce discomfort.\n");
          break;
        case 'e':
          printf("\nFor neck discomfort, try this gentle stretch:\n");
          printf("Slowly tilt your head to one side, bringing your ear toward "
                 "your shoulder. "
                 "Hold for 15 seconds and switch sides. Be cautious not to "
                 "force the stretch.\n");
          break;
        default:
          printf("Invalid choice! No specific area selected.\n");
          break;
        }
      } else {
        printf("Invalid choice! No specific seriousness level selected.\n");
      }
    } else {
      printf("Great to hear that you're not experiencing any physical "
             "discomfort. If you need further assistance, feel free to ask!\n");
    }
  } else {
    printf("It's wonderful to know that you're feeling %s! If you need more "
           "activities or assistance, let us know.\n",
           user->mood);
  }
}

// Function to simulate user interactions for automated tests
void simulateUserInteractions(User *user, const char *firstName, const char *lastName, const char *initialMood, char activityType, int activityChoicee, const char *postActivityMood) {
  strcpy(user->firstName, firstName);
  strcpy(user->lastName, lastName);
  // Simulate user providing the initial mood
  strcpy(user->mood, initialMood);

  // Simulate user choosing an activity type and an activity
  char choice = activityType;
  Activity *activityLibrary = getActivityLibrary(activityType);

   // Simulate user choosing an activity choice
 

  if (activityChoicee >= 1 && activityChoicee <= 3) {
    user->activity = &activityLibrary[activityChoicee - 1];

  // Simulate the post-activity mood check
  strcpy(user->mood, postActivityMood);

  displayUser(user);
  }
}

// Function to perform automated tests
void performAutomatedTests() {
  User user1;
  simulateUserInteractions(&user1, "John", "Doe", "Happy mood", 'a', 1, "Happy");

  User user2;
  simulateUserInteractions(&user2, "Alice", "Smith", "", 'b', 2, "Bored");

  User user3;
  simulateUserInteractions(&user3, "Bob", "Johnson", "Bored mood", 'c', 1, "Stressed");
}

int main() {
  // Uncomment the line below to run automated tests
  performAutomatedTests();

  // // The rest of your code remains unchanged
  // User user;

  // // Prompt user for name, mood, and activity
  // getUserName(&user);
  // getUserMood(&user);
  // getUserActivityType(&user);

  // // Display user information
  // displayUser(&user);

  // // Check post-activity mood and inquire about physical discomfort
  // postActivityMoodCheck(&user);

  return 0;
}
