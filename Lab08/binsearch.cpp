#include <iostream>
#include <fstream>

using namespace std;

void actualSort(int *, int, int);
int binsearch(int, int *, int, int);
void sort(int *, int);

int main(int argc, char *argv[]){
  int target;
  if(argc < 2){
    cout << "Provide a filename of the data to be searched" << endl;
    return 1;
  }
  ifstream datfile(argv[1], ios::in);
  if( datfile.fail() ){
    cout << "Unable to open file: " << argv[1] << endl;
    return 1;
  }
  int count = 0;
  // Count how many integers are in the file
  while(! datfile.fail()){
    int temp;
    datfile >> temp;
    if(!datfile.fail()){
      count++;
    }
  }
  // When we reach the end of the file, the EOF flag is set
  // To be able to read through the file again we need to clear that flag
  datfile.clear();
  //  We also need to set our internal position in the file back to 0
  datfile.seekg(0,ios::beg);

  // Now allocate an array to store the file data and read in the data
  int *data = new int[count];
  for(int i=0; i < count; i++){
    datfile >> data[i];
  }

  datfile.close();

  cout << "Read " << count << " integers from the data file.\n" << endl;
  cout << "Enter the target positive integer to search for: ";
  cin >> target;

  // Call selection sort
  sort(data, count);

  // Call binary search
  int retval = binsearch(target,data,0,count);

  // Interpret and print the results
  if(retval == -1){
    cout << target << " does not appear in the data." << endl;
  }
  else {
    cout << target << " appears at index " << retval << " in the data." << endl;
  }

  // Deallocate the data array
  delete [] data;
  return 0;
}



/***************************************************************
* Implements a recursive selection sort algorithm assuming that
*  the array is unsorted
***************************************************************/
void actualSort(int *data, int len, int counter)
{
  // Stops the sort when the considered array is only the last int, which must
  //  be sorted
  if(counter >= len-1)
  {
    return;
  }
  else
  {
    // Assumes the minimum value in the array is the first one
    int min = data[counter], minIndex = counter;
    // Checks the remainder of the array for a smaller minimum and remembers it
    //  and its index if found
    for(int i=counter+1; i < len; i++)
    {
      if(data[i] < min)
      {
        min = data[i];
        minIndex = i;
      }
    }

    // Swaps the first value with the smaller one if one was found
    if(min < data[counter])
    {
      data[minIndex] = data[counter];
      data[counter] = min;
    }

    // Sorts the remainder of the array not counting the minimum first value
    actualSort(data,len,counter+1);
  }
}

/**************************************************************
* Returns the index in the data array where target is located
*  or -1 if the target value is not in the list
**************************************************************/
int binsearch(int target, int *data, int start, int end)
{
  int midIndex = (start+end)/2;

  // The list is empty as soon as the start and end are the same
  if(start >= end)
  {
    return -1;
  }
// Check the middle element
  // If the middle value equals the target, return that index
  else if(data[midIndex] == target)
  {
    return midIndex;
  }
  // If the middle value is less than the target, check the right half of the 
  //  array
  else if(data[midIndex] < target)
  {
    return binsearch(target,data,midIndex+1,end);
  }
  // If the middle value is greater than the target, check the left half of the
  //  array
  else
  {
    return binsearch(target,data,start,midIndex);
  }
}

/*******************************************************
* Implements a selection sort algorithm to sort
*  the integer values in the 'data' array of size 'len'
*  assuming it isn't sorted already
* Relies on actualSort function
*******************************************************/
void sort(int *data, int len)
{
  // Counter remembers how many times variables have been swapped in the array
  //  as a starting point for the unsorted part
  int counter = 0;
  // The actual sorting happens here
  actualSort(data, len, counter);
}
