from ROOT import TStyle, kWhite, kTRUE
from ROOT import gROOT, gStyle
from ROOT import kGray, kAzure, kMagenta, kOrange, kWhite
from ROOT import kRed, kBlue, kGreen, kPink, kYellow
from ROOT import TLine, TLatex, TColor

from collections import namedtuple, OrderedDict
from math import sin, cos, tan, atan, exp, pi
from array import array

Plot_params = namedtuple('Params',
                         ['plotNumber',
                          'abscissa', 'ordinate',
                          'ymin', 'ymax',
                          'xmin', 'xmax',
                          'quotaName', 'iDrawEta',
                          'histoMin', 'histoMax',
                          'zLog', 'iRebin'])
plots = {}
plots.setdefault('x_vs_eta', Plot_params(10, '#eta', 'x/X_{0}', 0.0, 2.575, -4.0, 4.0, '', 0, 0., 0., 0, 1))
plots.setdefault('x_vs_phi', Plot_params(20, '#varphi [rad]', 'x/X_{0}', 0.0, 6.2, -4.0, 4.0, '', 0, 0., 0., 0, 1))
plots.setdefault('x_vs_R',   Plot_params(40, 'R [cm]', 'x/X_{0}', 0.0, 70.0, 0.0, 1200.0, '', 0, 0., 0., 0, 1))
plots.setdefault('l_vs_eta', Plot_params(10010, '#eta', 'x/#lambda_{I}', 0.0, 0.73, -4.0, 4.0, '', 0, 0., 0., 0, 1))
plots.setdefault('l_vs_phi', Plot_params(10020, '#varphi [rad]', 'x/#lambda_{I}', 0.0, 1.2, -4.0, 4.0, '', 0, 0., 0., 0, 1))
plots.setdefault('l_vs_R',   Plot_params(10040, 'R [cm]', 'x/#lambda_{I}', 0.0, 7.5, 0.0, 1200.0, '', 0, 0., 0., 0, 1))
plots.setdefault('x_vs_eta_vs_phi', Plot_params(30, '#eta', '#varphi', 0., 0., 0., 0., 'x/X_{0}', 0, -1., -1., 0, 1))
plots.setdefault('l_vs_eta_vs_phi', Plot_params(10030, '#eta', '#varphi', 0., 0., 0., 0., 'x/#lambda_{I}', 0, -1, -1, 0, 1))
plots.setdefault('x_vs_z_vs_Rsum', Plot_params(50, 'z [mm]', 'R [mm]', 0., 0., 0., 0., '#Sigmax/X_{0}', 1, -1., -1., 0, 0))
plots.setdefault('x_vs_z_vs_Rsumcos', Plot_params(52, 'z [mm]', 'R [mm]', 0., 0., 0., 0., '#Sigmax/X_{0}', 1, -1., -1., 0, 0))
#plots.setdefault('x_vs_z_vs_R', Plot_params(60, 'z [mm]', 'R [mm]', 0., 0., 0., 0., '1/X_{0}', 1, -1., -1., 0, 0))
plots.setdefault('x_vs_z_vs_Rloc', Plot_params(70, 'z [mm]', 'R [mm]', 0., 0., 0., 0., 'x/X_{0}', 1, -1., -1., 0, 0))
plots.setdefault('x_vs_z_vs_Rloccos', Plot_params(72, 'z [mm]', 'R [mm]', 0., 0., 0., 0., 'x/X_{0}', 1, -1., -1., 0, 0))
plots.setdefault('l_vs_z_vs_Rsum', Plot_params(10050, 'z [mm]', 'R [mm]', 0., 0., 0., 0., '#Sigmax/#lambda_{I}', 1, -1., -1., 0, 0))
plots.setdefault('l_vs_z_vs_Rsumcos', Plot_params(10052, 'z [mm]', 'R [mm]', 0., 0., 0., 0., '#Sigmax/#lambda_{I}', 1, -1., -1., 0, 0))
plots.setdefault('l_vs_z_vs_R', Plot_params(10060, 'z [mm]', 'R [mm]', 0., 0., 0., 0., '1/#lambda_{I}', 1, -1., -1., 0, 0))
plots.setdefault('l_vs_z_vs_Rloc', Plot_params(10070, 'z [mm]', 'R [mm]', 0., 0., 0., 0., 'x/#lambda_{I}', 1, -1., -1., 0, 0))
plots.setdefault('l_vs_z_vs_Rloccos', Plot_params(10072, 'z [mm]', 'R [mm]', 0., 0., 0., 0., 'x/#lambda_{I}', 1, -1., -1., 0, 0))
plots.setdefault('x_over_l_vs_eta', Plot_params(10, '#eta', '(x/X_{0})/(x/#lambda_{I})', 0., 0., 0., 0., '', 0, -1, -1, 0, 0))
plots.setdefault('x_over_l_vs_phi', Plot_params(20, '#varphi [rad]', '(x/X_{0})/(x/#lambda_{I})', 0., 0., 0., 0., '', 0, -1, -1, 0, 0))

# Conversion name from the label (key) to the components in CMSSW/Geometry
_LABELS2COMPS = {'BeamPipe': 'BEAM',
                 'Tracker': 'Tracker',
                 'Pixel':   ['PixelBarrel', 'PixelForwardZplus', 'PixelForwardZminus'],
                 'PixBar':  'PixelBarrel',
                 'PixFwd':  ['PixelForwardZplus', 'PixelForwardZminus', 'PixelForward'],
                 'PixFwdMinus': 'PixelForwardZminus',
                 'PixFwdPlus':  'PixelForwardZplus',
                 'TIB':         'TIB',
                 'TOB':         'TOB',
                 'TIDB':        'TIDB',
                 'TIDF':        'TIDF',
                 'TEC':         'TEC',
                 'InnerServices': ['TIBTIDServicesF', 'TIBTIDServicesB'],
                 'TkStrct': ['TrackerOuterCylinder', 'TrackerBulkhead'],
                 'Phase2PixelBarrel': 'Phase2PixelBarrel',
                 'Phase2OTBarrel': 'Phase2OTBarrel',
                 'Phase2PixelEndcap': 'Phase2PixelEndcap',
                 'Phase2OTForward': 'Phase2OTForward',
                 'HGCal': 'HGCal',
                 'HGCalEE': 'HGCalEE',
                 'HGCalHE': ['HGCalHEsil', 'HGCalHEmix']
                 }

# Compounds are used to stick together different part of the Tracker
# detector, so that their cumulative material description can be
# derived. The key name can be generic, while the names in the
# associated list must be such that an appropriate material
# description file, in ROOT format, is present while producing the
# cumulative plot. A missing element will invalidate the full
# procedure.
COMPOUNDS = OrderedDict()
COMPOUNDS["Tracker"] = ["Tracker"]
COMPOUNDS["TrackerSum"] = ["TIB", "TIDF", "TIDB",
                           "BeamPipe", "InnerServices",
                           "TOB", "TEC",
                           "TkStruct",
                           "PixBar", "PixFwdPlus", "PixFwdMinus"]
COMPOUNDS["TrackerSumPhaseII"] = ["BeamPipe",
                                  "Phase2PixelBarrel",
                                  "Phase2OTBarrel", "Phase2OTForward",
                                  "Phase2PixelEndcap"]
COMPOUNDS["Pixel"] = ["PixBar", "PixFwdMinus", "PixFwdPlus"]
COMPOUNDS["Strip"] = ["TIB", "TIDF", "TIDB", "InnerServices", "TOB", "TEC"]
COMPOUNDS["InnerTracker"] = ["TIB", "TIDF", "TIDB", "InnerServices"]
COMPOUNDS["HGCal"] = ["HGCal"]
COMPOUNDS["HGCalEE"] = ["HGCalEE"]
COMPOUNDS["HGCalHE"] = ["HGCalHEsil", "HGCalHEmix"]


# The DETECTORS must be the single component of the tracker for which
# the user can ask for the corresponding material description.
DETECTORS = OrderedDict()
DETECTORS["BeamPipe"] = kGray+2
DETECTORS["InnerServices"] = kGreen+2
DETECTORS["PixBar"] = kAzure-5
DETECTORS["Phase1PixelBarrel"] = kAzure-5
DETECTORS["Phase2PixelBarrel"] = kAzure-5
DETECTORS["PixFwdPlus"] = kAzure-9
DETECTORS["PixFwdMinus"] = kAzure-9
DETECTORS["Phase2PixelEndcap"] = kAzure-9
DETECTORS["Phase2OTBarrel"] = kMagenta-2
DETECTORS["Phase2OTForward"] = kOrange-2
DETECTORS["TIB"] = kMagenta-6
DETECTORS["TIDF"] = kMagenta+2
DETECTORS["TIDB"] = kMagenta+2
DETECTORS["TOB"] = kOrange+10
DETECTORS["TEC"] = kOrange-2
DETECTORS["HGCal"] = kAzure-5
DETECTORS["HGCalEE"] = kAzure-9
DETECTORS["HGCalHE"] = kOrange-2

# sDETS are the label of the Tracker elements in the Reconstruction
# geometry. They are all used to derive the reconstruction material
# profile to be compared to the one obtained directly from the
# simulation. A missing key in the real reconstruction geometry is not
# a problem, since this will imply that the corresponding plotting
# routine will skip that missing part. For this reason this map can be
# made as inclusive as possible with respect to the many
# reconstruction geometries in CMSSW.
sDETS = OrderedDict()
sDETS["PXB"] = kRed
sDETS["PXF"] = kBlue
sDETS["TIB"] = kGreen
sDETS["TID"] = kYellow
sDETS["TOB"] = kOrange
sDETS["TEC"] = kPink

# hist_label_to_num contains the logical names of the Tracker detector
# that holds material. They are therefor not aware of which detector
# they belong to, but they are stored in specific plots in all the
# mat*root files produced. The numbering of the plots is identical
# across all files.
hist_label_to_num = OrderedDict()
'''
hist_label_to_num['COP'] = [100, 13, 'Copper'] # Index first, color second, legend label third
hist_label_to_num['SCI'] = [200, 27, 'Scintillator']
hist_label_to_num['CAB'] = [300, 46, 'Cables']
hist_label_to_num['MNE'] = [400, 38, 'M_NEMA_FR4 plate']
hist_label_to_num['SIL'] = [500, 30, 'Silicon']
hist_label_to_num['OTH'] = [600, 42, 'Other']
hist_label_to_num['AIR'] = [700, 29, 'Air']
hist_label_to_num['SST'] = [800, 40, 'Stainless Steel']
hist_label_to_num['WCU'] = [900, 33, 'WCu']
hist_label_to_num['LEA'] = [1000, 31, 'Lead']
'''

hist_label_to_num['COP'] = [100, 2, 'Copper'] # Index first, color second, legend label third
hist_label_to_num['SCI'] = [200, 3, 'Scintillator']
hist_label_to_num['CAB'] = [300, 4, 'Cables']
hist_label_to_num['MNE'] = [400, 5, 'M_NEMA_FR4 plate']
hist_label_to_num['SIL'] = [500, 6, 'Silicon']
hist_label_to_num['OTH'] = [600, 7, 'Other']
hist_label_to_num['AIR'] = [700, 8, 'Air']
hist_label_to_num['SST'] = [800, 9, 'Stainless Steel']
hist_label_to_num['WCU'] = [900, 28, 'WCu']
hist_label_to_num['LEA'] = [1000, 12, 'Lead']

def setTDRStyle():
    """Function to setup a TDR-like style"""

    tdrStyle = TStyle("tdrStyle","Style for P-TDR")

    # For the canvas:
    tdrStyle.SetCanvasBorderMode(0)
    tdrStyle.SetCanvasColor(kWhite)
    tdrStyle.SetCanvasDefH(600) #Height of canvas
    tdrStyle.SetCanvasDefW(600) #Width of canvas
    tdrStyle.SetCanvasDefX(0)   #POsition on screen
    tdrStyle.SetCanvasDefY(0)

    # For the Pad:
    tdrStyle.SetPadBorderMode(0)
    tdrStyle.SetPadColor(kWhite)
    tdrStyle.SetPadGridX(False)
    tdrStyle.SetPadGridY(False)
    tdrStyle.SetGridColor(0)
    tdrStyle.SetGridStyle(3)
    tdrStyle.SetGridWidth(1)

    # For the frame:
    tdrStyle.SetFrameBorderMode(0)
    tdrStyle.SetFrameBorderSize(1)
    tdrStyle.SetFrameFillColor(0)
    tdrStyle.SetFrameFillStyle(0)
    tdrStyle.SetFrameLineColor(1)
    tdrStyle.SetFrameLineStyle(1)
    tdrStyle.SetFrameLineWidth(1)

    # For the histo:
    tdrStyle.SetHistLineColor(1)
    tdrStyle.SetHistLineStyle(0)
    tdrStyle.SetHistLineWidth(1)
    tdrStyle.SetEndErrorSize(2)
    tdrStyle.SetErrorX(0.)
    tdrStyle.SetMarkerStyle(20)

    #For the fit/function:
    tdrStyle.SetOptFit(1)
    tdrStyle.SetFitFormat("5.4g")
    tdrStyle.SetFuncColor(2)
    tdrStyle.SetFuncStyle(1)
    tdrStyle.SetFuncWidth(1)

    #For the date:
    tdrStyle.SetOptDate(0)

    # For the statistics box:
    tdrStyle.SetOptFile(0)
    tdrStyle.SetOptStat(0); # To display the mean and RMS:   SetOptStat("mr")
    tdrStyle.SetStatColor(kWhite)
    tdrStyle.SetStatFont(42)
    tdrStyle.SetStatFontSize(0.025)
    tdrStyle.SetStatTextColor(1)
    tdrStyle.SetStatFormat("6.4g")
    tdrStyle.SetStatBorderSize(1)
    tdrStyle.SetStatH(0.1)
    tdrStyle.SetStatW(0.15)

    # Margins:
    tdrStyle.SetPadTopMargin(0.05)
    tdrStyle.SetPadBottomMargin(0.13)
    tdrStyle.SetPadLeftMargin(0.16)
    tdrStyle.SetPadRightMargin(0.02)

    # For the Global title:
    tdrStyle.SetOptTitle(0)
    tdrStyle.SetTitleFont(42)
    tdrStyle.SetTitleColor(1)
    tdrStyle.SetTitleTextColor(1)
    tdrStyle.SetTitleFillColor(10)
    tdrStyle.SetTitleFontSize(0.05)

    # For the axis titles:
    tdrStyle.SetTitleColor(1, "XYZ")
    tdrStyle.SetTitleFont(42, "XYZ")
    tdrStyle.SetTitleSize(0.06, "XYZ")
    tdrStyle.SetTitleXOffset(0.9)
    tdrStyle.SetTitleYOffset(1.0)

    # For the axis labels:
    tdrStyle.SetLabelColor(1, "XYZ")
    tdrStyle.SetLabelFont(42, "XYZ")
    tdrStyle.SetLabelOffset(0.007, "XYZ")
    tdrStyle.SetLabelSize(0.05, "XYZ")

    # For the axis:
    tdrStyle.SetAxisColor(1, "XYZ")
    tdrStyle.SetStripDecimals(kTRUE)
    tdrStyle.SetTickLength(0.03, "XYZ")
    tdrStyle.SetNdivisions(510, "XYZ")
    tdrStyle.SetPadTickX(1)  # To get tick marks on the opposite side of the frame
    tdrStyle.SetPadTickY(1)

    # Change for log plots:
    tdrStyle.SetOptLogx(0)
    tdrStyle.SetOptLogy(0)
    tdrStyle.SetOptLogz(0)

    # Postscript options:
    tdrStyle.SetPaperSize(20.,20.)

    tdrStyle.cd()

def drawEtaValues():
    """Function to draw the eta.

    Function to draw the eta references on top of an already existing
    TCanvas. The lines and labels drawn are collected inside a list and
    the list is returned to the user to extend the live of the objects
    contained, otherwise no lines and labels will be drawn, since they
    will be garbage-collected as soon as this function returns.
    """

    # Add eta labels
    keep_alive = []
    etas = [-3.4, -3.0, -2.8, -2.6, -2.4, -2.2,
            -2.0, -1.8, -1.6, -1.4, -1.2, -1., -0.8, -0.6, -0.4, -0.2, 0., 0.2,
            0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2., 2.2, 2.4, 2.6, 2.8, 3.0,
            3.4]

    etax = 2940.
    etay = 1240.
    lineL = 100.
    offT = 10.

    for ieta in etas:
        th = 2*atan(exp(-ieta))
        talign = 21

        #IP
        lineh = TLine(-20.,0.,20.,0.)
        lineh.Draw()
        linev = TLine(0.,-10.,0.,10.)
        linev.Draw()
        keep_alive.append(lineh)
        keep_alive.append(linev)

        x1 = 0
        y1 = 0
        if ieta>-1.6 and ieta<1.6:
            x1 = etay/tan(th)
            y1 = etay
        elif ieta <=-1.6:
            x1 = -etax
            y1 = -etax*tan(th)
            talign = 11
        elif ieta>=1.6:
            x1 = etax
            y1 = etax*tan(th)
            talign = 31
        x2 = x1+lineL*cos(th)
        y2 = y1+lineL*sin(th)
        xt = x2
        yt = y2+offT

        line1 = TLine(x1,y1,x2,y2)
        line1.Draw()
        keep_alive.append(line1)

        text = "%3.1f" % ieta
        t1 = TLatex(xt, yt, '%s' % ('#eta = 0' if ieta == 0 else text))
        t1.SetTextSize(0.03)
        t1.SetTextAlign(talign)
        t1.Draw()
        keep_alive.append(t1)
    return keep_alive

def TwikiPrintout(plotname, label, zoom): 
    """The plots in the twiki are already too much and to avoid mistakes 
       we will try to automatize the procedure
    """

    #Twiki will strip out spaces
    label = label.replace(" ", "_")

    zoomstring = ""
    
    if zoom == "all":
        zoomstring = ""
        zoomtitle = "in all HGCal"
    elif zoom == "zplus":
        zoomstring = "_ZplusZoom"
        zoomtitle = "in Z+ endcap of HGCal"
    elif zoom == "zminus":
        zoomstring = "_ZminusZoom"
        zoomtitle = "in Z- endcap of HGCal"
    else :
        print "WRONG OPTION"
    

    #Here for the hide button
    if plotname == "x_vs_z_vs_Rsum":
        print "%%TWISTY{ mode=\"div\" showlink=\"Click to see the %s plots %s \" hidelink=\"Hide %s %s\" showimgright=\"%%ICONURLPATH{toggleopen-small}%%\" hideimgright=\"%%ICONURLPATH{toggleclose-small}%%\"}%%" % (label,zoomtitle, label, zoomtitle)
    
    if "Rsum" in plotname and "x_vs" in plotname and not "cos" in plotname: 
        print "| <img alt=\"HGCal_%s%s%s.png\" height=\"300\" width=\"550\" src=\"%%ATTACHURLPATH%%/HGCal_%s%s%s.png\" /> | The plot on the left shows the 2D profile histogram for *%s* %s that displays the mean value of the material budget in units of radiation length in each R-z cell. R-z cell is 1 cm x 1 mm. The plot depicts the accumulated material budget as seen by the track, as the track travels throughout the detector.|" % (plotname,label,zoomstring, plotname,label,zoomstring, label, zoomtitle)

    if "Rsum" in plotname and "l_vs" in plotname and not "cos" in plotname: 
        print "| <img alt=\"HGCal_%s%s%s.png\" height=\"300\" width=\"550\" src=\"%%ATTACHURLPATH%%/HGCal_%s%s%s.png\" /> | The plot on the left shows the 2D profile histogram for *%s* %s that displays the mean value of the material budget in units of interaction length in each R-z cell. R-z cell is 1 cm x 1 mm. The plot depicts the accumulated material budget as seen by the track, as the track travels throughout the detector.|" % (plotname,label,zoomstring, plotname,label,zoomstring, label, zoomtitle)
     
    if "Rsumcos" in plotname and "x_vs" in plotname: 
        print "| <img alt=\"HGCal_%s%s%s.png\" height=\"300\" width=\"550\" src=\"%%ATTACHURLPATH%%/HGCal_%s%s%s.png\" /> | The plot on the left shows the 2D profile histogram for *%s* %s that displays the mean value of the material budget in units of radiation length in each R-z cell. R-z cell is 1 cm x 1 mm. The plot depicts the orthogonal accumulated material budget, that is cos(theta) what the track sees.|" % (plotname,label,zoomstring, plotname,label,zoomstring, label, zoomtitle)

    if "Rsumcos" in plotname and "l_vs" in plotname: 
        print "| <img alt=\"HGCal_%s%s%s.png\" height=\"300\" width=\"550\" src=\"%%ATTACHURLPATH%%/HGCal_%s%s%s.png\" /> | The plot on the left shows the 2D profile histogram for *%s* %s that displays the mean value of the material budget in units of interaction length in each R-z cell. R-z cell is 1 cm x 1 mm. The plot depicts the orthogonal accumulated material budget, that is cos(theta) what the track sees.|" % (plotname,label,zoomstring, plotname,label,zoomstring, label, zoomtitle)
     
    if "Rloc" in plotname and "x_vs" in plotname and not "cos" in plotname: 
         print "| <img alt=\"HGCal_%s%s%s.png\" height=\"300\" width=\"550\" src=\"%%ATTACHURLPATH%%/HGCal_%s%s%s.png\" /> | The plot on the left shows the 2D profile histogram for *%s* %s that displays the local mean value of the material budget in units of radiation length in each R-z cell. R-z cell is 1 cm x 1 mm. The plot depicts the local material budget as seen by the track, as the track travels throughout the detector.|"% (plotname,label,zoomstring, plotname,label,zoomstring, label, zoomtitle)

    if "Rloc" in plotname and "l_vs" in plotname and not "cos" in plotname: 
         print "| <img alt=\"HGCal_%s%s%s.png\" height=\"300\" width=\"550\" src=\"%%ATTACHURLPATH%%/HGCal_%s%s%s.png\" /> | The plot on the left shows the 2D profile histogram for *%s* %s that displays the local mean value of the material budget in units of interaction length in each R-z cell. R-z cell is 1 cm x 1 mm. The plot depicts the local material budget as seen by the track, as the track travels throughout the detector.|"% (plotname,label,zoomstring, plotname,label,zoomstring, label, zoomtitle)

    #Here again for the closing of the hide button
    if plotname == "l_vs_z_vs_Rloc":
        print "%ENDTWISTY%"

    """ 
    I won't put the local cos plots for now, only the sum cos above
    if "Rloccos" in plotname and "x_vs" in plotname: 
         print "| <img alt=\"HGCal_%s%s%s.png\" height=\"300\" width=\"550\" src=\"%%ATTACHURLPATH%%/HGCal_%s%s%s.png\" /> | The plot on the left shows the 2D profile histogram for *%s* %s that displays the local mean value of the material budget in units of radiation length in each R-z cell. R-z cell is 1 cm x 1 mm. The plot depicts the orthogonal accumulated material budget, that is cos(theta) what the track sees.|"% (plotname,label,zoomstring, plotname,label,zoomstring, label, zoomtitle)

    if "Rloccos" in plotname and "l_vs" in plotname: 
         print "| <img alt=\"HGCal_%s%s%s.png\" height=\"300\" width=\"550\" src=\"%%ATTACHURLPATH%%/HGCal_%s%s%s.png\" /> | The plot on the left shows the 2D profile histogram for *%s* %s that displays the local mean value of the material budget in units of interaction length in each R-z cell. R-z cell is 1 cm x 1 mm. The plot depicts the orthogonal accumulated material budget, that is cos(theta) what the track sees.|"% (plotname,label,zoomstring, plotname,label,zoomstring, label, zoomtitle)
    """
 
def acustompalette(): 
    NRGBs = 7
    NCont = 100
    ncolors = array('i', [])
    gStyle.SetNumberContours(NCont);
    stops   = [ 0.00, 0.10, 0.25, 0.45, 0.60, 0.75, 1.00 ]
    red     = [ 1.00, 0.00, 0.00, 0.00, 0.97, 0.97, 0.10 ]
    green   = [ 1.00, 0.97, 0.30, 0.40, 0.97, 0.00, 0.00 ]
    blue    = [ 1.00, 0.97, 0.97, 0.00, 0.00, 0.00, 0.00 ]
    stopsArray = array('d', stops)
    redArray = array('d', red)
    greenArray = array('d', green)
    blueArray = array('d', blue)
    first_color_number = TColor.CreateGradientColorTable(NRGBs, stopsArray, redArray, greenArray, blueArray, NCont);
    gStyle.SetNumberContours(NCont)


    palsize = NCont
    palette = []
    for i in range(palsize):
        palette.append(first_color_number+i)
        palarray = array('i',palette)

    gStyle.SetPalette(palsize,palarray)


#In MeV/mm
dEdx = OrderedDict()
dEdx['Copper'] = 1.257
dEdx['H_Scintillator'] = 0.3952 #C
dEdx['Cables'] = 0.#????????? <<<<<<<<<===============
dEdx['M_NEMA_FR4_plate'] = 0.
dEdx['Silicon'] = 0.3876
dEdx['Other'] = 0.
dEdx['Air'] = 0.
#--------
dEdx['Fe'] = 1.143
dEdx['Mn'] = 1.062
dEdx['Cr'] = 1.046
dEdx['Ni'] = 1.307
dEdx['StainlessSteel'] = 0.7*dEdx['Fe']+0.01*dEdx['Mn']+0.19*dEdx['Cr']+0.1*dEdx['Ni'];
#-------- 
dEdx['W'] = 2.210
dEdx['Cu'] = 1.257
dEdx['WCu'] = 0.75*dEdx['W']+0.25*dEdx['Cu']
#--------
dEdx['Lead'] = 1.274 #Pb

#In mm
MatXo = OrderedDict()
MatXo['Copper'] = 14.3559
MatXo['H_Scintillator'] = 425.393
MatXo['Cables'] = 66.722
MatXo['M_NEMA_FR4_plate'] = 175.056
MatXo['Silicon'] = 93.6762
MatXo['Other'] = 0.
MatXo['Air'] = 301522.
MatXo['StainlessSteel'] = 17.3555
MatXo['WCu'] = 5.1225
MatXo['Lead'] = 5.6118
