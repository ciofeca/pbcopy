# pbcopy
Command-line utility: copy text from stdin to Qt pastebuffer in Sailfish OS.

Current version has been tested on SailfishOS 2.2.

# use case
Scenario 1: you have a SailfishOS device with Developer Mode enabled (that is: *root* privileges and *ssh* user access) and you want to "paste" on it some text copied from your local computer.

Scenario 2: at 6am some *bash* script queries some website and "pastes" news ready for you to text in the messaging app.

# how does it work
Qt5 applications are allowed to read/change the paste-buffer contents: *pbcopy* is a minimal SailfishApp (barely 13 kilobytes executable file) that initializes an appwindow, copies the text into the paste buffers, and shuts down in a couple seconds without user interaction.

# compiling
We are *not* actually going to build an actual RPM package because new SailfishOS developer rules require *harbour-...* naming and icons package. Thus:

* load the *pbcopy.pro* project in SailfishOS SDK
* select *Build / Open Build and Kit Selector...* and select Build=*Release*, Deploy=*By Building an RPM package*
* select *Build / Clean project "pbcopy"*
* select *Build / Deploy project "pbcopy"*

The build will stop with a non-critical error ("file not found icons apps etc").

# installing
We extract the executable file (we don't care about the RPM) from the virtual machine where it was built, and then copy it to the SailfishOS device and then move it to the */usr/bin* directory (change the "SFOS=..." definition to suit your local network needs):

* copy the executable file from the virtual machine where it was built to local */tmp* and then from local */tmp* to the SailfishOS device, then move it to */usr/bin/* of the device (change the SFOS definition according to your local network):

    SSHMER='ssh -p 2222 -i /opt/SailfishOS/vmshare/ssh/private_keys/engine/mersdk'
    rsync -ave "$SSHMER" mersdk@localhost:/home/deploy/installroot/usr/bin/pbcopy /tmp/

    SFOS='xperia'
    rsync -ave ssh /tmp/pbcopy nemo@$SFOS:/tmp/
    echo $YOUR_SFOS_ROOT_PASSWORD | ssh nemo@$SFOS devel-su mv -v /tmp/pbcopy /usr/bin/

If everything went well, the last command will say something like: *Password: /tmp/pbcopy -> /usr/bin/pbcopy, removed /tmp/pbcopy*

# usage examples
* *[nemo@Jolla ~]$* echo "If we come to a minefield, our infantry attacks exactly as it were not there." | pbcopy
* *[nemo@Sailfish ~]$* head -1 file.txt | pbcopy File begins with:
* *[me@linuxpc ~]$* cat /proc/uptime | ssh $SFOS pbcopy
