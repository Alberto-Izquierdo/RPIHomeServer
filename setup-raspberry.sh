# Create the .bashrc if it does not exist
touch ~/.bashrc
# Execute the iot project when the raspberry is turned on
echo "sudo ./iot_project &" >> ~/.bashrc
