// Empty interrupt handler
void handle_interrupt (unsigned _irq)
{ }

int main()
{ 
  // Create a pointer called VGA that points to the drawing area
  volatile char *VGA = (volatile char*) 0x08000000;

  // Clear the entire VGA buffer area by writing the value 0 (=black)
  for (int i = 0; i < 320*480; i++)
    VGA[i] = 0;  

  // Draw five rows of white pixels (remember that screen is 320 pixels wide and the color 255 is white)
  for (int i = 0; i < 320*5; i++)
  VGA[320*118 + i] = 255;

  // Enter a forever loop
  while (1)
    { }
}
