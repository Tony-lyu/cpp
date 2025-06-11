#include <iostream>
#include <cstring>
using namespace std;

int main() {
  struct tvseries {
    char* series_name;
    int original_release_year;
    struct tv_episode {
      char episode_name [ 30 ];
      int episode_number;
      string episode_release_date;
   };
   struct {
      int season_number;
      int season_release_year;
      tv_episode episodes[5];
   } seasons[3], *seasons_ptr;
  } some_tv_series, *ptr_some_tv_series = &some_tv_series;

  ptr_some_tv_series->series_name = new char[strlen("Black Mirror") + 1];
  strcpy(ptr_some_tv_series->series_name, "Black Mirror");
  ptr_some_tv_series->original_release_year = 2009;
  ptr_some_tv_series->seasons[0].season_number = 3;
  ptr_some_tv_series->seasons[0].season_release_year = 2016;

  ptr_some_tv_series->seasons[1].season_number = 4;
  ptr_some_tv_series->seasons[1].season_release_year = 2017;

  ptr_some_tv_series->seasons[2].season_number = 6;
  ptr_some_tv_series->seasons[2].season_release_year = 2023;
  
  strcpy(ptr_some_tv_series->seasons[0].episodes[0].episode_name, "Nosedive");
  ptr_some_tv_series->seasons[0].episodes[0].episode_number = 1;
  ptr_some_tv_series->seasons[0].episodes[0].episode_release_date = "2016-10-21";
  
  strcpy(ptr_some_tv_series->seasons[0].episodes[1].episode_name, "Playtest");
  ptr_some_tv_series->seasons[0].episodes[1].episode_number = 2;
  ptr_some_tv_series->seasons[0].episodes[1].episode_release_date = "2016-10-21";
  
  strcpy(ptr_some_tv_series->seasons[0].episodes[2].episode_name, "Shut Up and Dance");
  ptr_some_tv_series->seasons[0].episodes[2].episode_number = 3;
  ptr_some_tv_series->seasons[0].episodes[2].episode_release_date = "2016-10-21";
  
  strcpy(ptr_some_tv_series->seasons[0].episodes[3].episode_name, "San Junipero");
  ptr_some_tv_series->seasons[0].episodes[3].episode_number = 4;
  ptr_some_tv_series->seasons[0].episodes[3].episode_release_date = "2016-10-21";

  strcpy(ptr_some_tv_series->seasons[0].episodes[4].episode_name, "Men Against Fire");
  ptr_some_tv_series->seasons[0].episodes[4].episode_number = 4;
  ptr_some_tv_series->seasons[0].episodes[4].episode_release_date = "2016-10-21";

  strcpy(ptr_some_tv_series->seasons[1].episodes[0].episode_name, "USS Callister");
  ptr_some_tv_series->seasons[1].episodes[0].episode_number = 1;
  ptr_some_tv_series->seasons[1].episodes[0].episode_release_date = "2017-12-29";
  
  strcpy(ptr_some_tv_series->seasons[1].episodes[1].episode_name, "Arkangel");
  ptr_some_tv_series->seasons[1].episodes[1].episode_number = 2;
  ptr_some_tv_series->seasons[1].episodes[1].episode_release_date = "2017-12-29";

  strcpy(ptr_some_tv_series->seasons[1].episodes[2].episode_name, "Crocodile");
  ptr_some_tv_series->seasons[1].episodes[2].episode_number = 3;
  ptr_some_tv_series->seasons[1].episodes[2].episode_release_date = "2017-12-29";

  strcpy(ptr_some_tv_series->seasons[1].episodes[3].episode_name, "Hang the DJ");
  ptr_some_tv_series->seasons[1].episodes[3].episode_number = 4;
  ptr_some_tv_series->seasons[1].episodes[3].episode_release_date = "2017-12-29";

  strcpy(ptr_some_tv_series->seasons[1].episodes[4].episode_name, "Metalhead");
  ptr_some_tv_series->seasons[1].episodes[4].episode_number = 5;
  ptr_some_tv_series->seasons[1].episodes[4].episode_release_date = "2017-12-29";

  strcpy(ptr_some_tv_series->seasons[2].episodes[0].episode_name, "Joan is Awful");
  ptr_some_tv_series->seasons[2].episodes[0].episode_number = 1;
  ptr_some_tv_series->seasons[2].episodes[0].episode_release_date = "2023-06-15";

  strcpy(ptr_some_tv_series->seasons[2].episodes[1].episode_name, "Loch Henry");
  ptr_some_tv_series->seasons[2].episodes[1].episode_number = 2;
  ptr_some_tv_series->seasons[2].episodes[1].episode_release_date = "2023-06-15";

  strcpy(ptr_some_tv_series->seasons[2].episodes[2].episode_name, "Beyond the Sea");
  ptr_some_tv_series->seasons[2].episodes[2].episode_number = 3;
  ptr_some_tv_series->seasons[2].episodes[2].episode_release_date = "2023-06-15";

  strcpy(ptr_some_tv_series->seasons[2].episodes[3].episode_name, "Mazey Day");
  ptr_some_tv_series->seasons[2].episodes[3].episode_number = 4;
  ptr_some_tv_series->seasons[2].episodes[3].episode_release_date = "2023-06-15";

  strcpy(ptr_some_tv_series->seasons[2].episodes[4].episode_name, "Demon 79");
  ptr_some_tv_series->seasons[2].episodes[4].episode_number = 5;
  ptr_some_tv_series->seasons[2].episodes[4].episode_release_date = "2023-06-15";


  cout << "TV Series: " << some_tv_series.series_name << endl;
  cout << "Original Release Year: ";  
  cout << some_tv_series.original_release_year << endl;
  for (int i = 0; i < 3; i++) {
    cout << "Season " << some_tv_series.seasons[i].season_number << endl;
    cout <<"Release Year: " << some_tv_series.seasons[i].season_release_year;
    cout << endl;
    for (int j = 0; j < 5; j++) {
      cout << "  Episode " << some_tv_series.seasons[i].episodes[j].episode_number;
      cout << ": "
           << some_tv_series.seasons[i].episodes[j].episode_name << ", Release Date: "
           << some_tv_series.seasons[i].episodes[j].episode_release_date << endl;
    }
  }



  ptr_some_tv_series = new tvseries;
  ptr_some_tv_series->series_name = new char[strlen("Black Mirror") + 1];
  strcpy(ptr_some_tv_series->series_name, "Black Mirror");
  ptr_some_tv_series->original_release_year = 2009;
  ptr_some_tv_series->seasons[0].season_number = 3;
  ptr_some_tv_series->seasons[0].season_release_year = 2016;
  for (int i = 0; i < 3; ++i) {
      ptr_some_tv_series->seasons[i].season_number = i;
      ptr_some_tv_series->seasons[i].season_release_year = i + 2015;

      for (int j = 0; j < 5; ++j) {
        ptr_some_tv_series->seasons[i].episodes[j].episode_number = j + 1;
        strcpy(ptr_some_tv_series->seasons[i].episodes[j].episode_name, 
          ("Episode " + to_string(j + 1)).c_str());
        ptr_some_tv_series->seasons[i].episodes[j].episode_release_date = "2020-01-01"; 
      }
  }

  cout << "TV Series: " << ptr_some_tv_series->series_name << endl;
  cout << "Original Release Year: " << ptr_some_tv_series->original_release_year
    << endl;
  for (int i = 0; i < 3; ++i) {
      cout << "Season " << ptr_some_tv_series->seasons[i].season_number << ", Release Year: " << ptr_some_tv_series->seasons[i].season_release_year << endl;
      for (int j = 0; j < 5; ++j) {
          cout << "  Episode " 
            << ptr_some_tv_series->seasons[i].episodes[j].episode_number << ": "
            << ptr_some_tv_series->seasons[i].episodes[j].episode_name
            << ", Release Date: "
            << ptr_some_tv_series->seasons[i].episodes[j].episode_release_date << endl;
      }
  }
}
  
