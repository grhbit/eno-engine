# Version Increase Script
# version.rb

def getVersion(destfilename)
	@major = 0
	@minor = 0
	@revision = 0
	IO.foreach(destfilename) {
		|line| 
		@major = $1 if line =~ /major = (\d+)/
		@minor = $1 if line =~ /minor = (\d+)/
		@revision = $1 if line =~ /revision = (\d+)/
	}
	
	return Integer(@major), Integer(@minor), Integer(@revision)
end

def isMac?
	RUBY_PLATFORM.downcase.include?("darwin")
end

def isWindows?
	RUBY_PLATFORM.downcase.include?("mswin")
end

def isLinux?
	RUBY_PLATFORM.downcase.include?("linux")
end

Dir.chdir("../Scripts/")
destfilename = "version.cpp"
tempfilename = "version.cpp.tmp"
time = Time.now
major, minor, revision = 0, 0, 0

if isWindows?
	localtime = time.localtime.to_s + "\"\n// mswin-Visual Studio\n"
elsif isMac?
	localtime = `date` + "\"\n// darwin-Xcode\n"
elsif isLinux?
	localtime = `date` + "\"\n// linux\n"
end

localtime.strip!

File.delete(tempfilename) if File.exist?(tempfilename)

if File.exist?(destfilename)
	major, minor, revision = getVersion(destfilename)
	revision += 1
end

tempfile = File.new(tempfilename, 'w')
tempfile.write 	"// Version Info\n" +
				"#include \"enoType.hpp\"\n" +
				"\n" +
				"const unsigned int eno_major = " + major.to_s + ";\n" +
				"const unsigned int eno_minor = " + minor.to_s + ";\n" +
				"const unsigned int revision = " + revision.to_s + ";\n" +
				"const char *const date = \"" + time.gmtime.to_s + "\";\n" +
				"//          local time = \"" + localtime.to_s
tempfile.close

File.rename(tempfilename, destfilename)

# ex) version.cpp
#!	-	-	-	-	-	-
#!// Version Info
#!#include "enoType.hpp"
#!
#!const unsigned int eno_major = 0
#!const unsigned int eno_minor = 0
#!const unsigned int revision = 0
#!const char *const date = "Sat Dec 24 13:06:15 UTC 2011"
#!//          Local Time = "Sat Dec 24 22:06:15 KST 2011"
#!// darwin-Xcode
#!	-	-	-	-	-	-