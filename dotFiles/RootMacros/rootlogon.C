void rootlogon()
{
  // Load ATLAS style
  std::cout << "Loading Atlas Style" << std::endl;
  gROOT->LoadMacro("AtlasStyle.C");
  gROOT->ProcessLine("SetAtlasStyle()");
}
