import FWCore.ParameterSet.Config as cms

process = cms.Process( "RawDataConverter" )

process.source = cms.Source("NewEventStreamFileReader",
  fileNames = cms.untracked.vstring()
)

process.source.fileNames.extend(cms.untracked.vstring(
        '__INPUT_FILENAMES_IN_DAT_FORMAT__'
        ))

# Choose how many events should be processed
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32( -1 )
)

# Message Logger
process.load("DQM.SiStripCommon.MessageLogger_cfi")


process.load("OnlineDB.SiStripConfigDb.SiStripConfigDb_cfi")
process.SiStripConfigDb.UsingDb = True                    # should be true!
process.SiStripConfigDb.ConfDb = 'user/password@account'  # taken from $CONFDB
process.SiStripConfigDb.Partitions = cms.untracked.PSet(
        PrimaryPartition = cms.untracked.PSet(
             PartitionName = cms.untracked.string('TM_09-JUN-2009_1'),
             RunNumber     = cms.untracked.uint32(213694)
        ),
        TIB = cms.untracked.PSet(
              PartitionName = cms.untracked.string('TI_27-JAN-2010_2'),
         ),
        TOB = cms.untracked.PSet(
            PartitionName = cms.untracked.string('TO_30-JUN-2009_1')
        ),
        TECP = cms.untracked.PSet(
           PartitionName = cms.untracked.string('TP_09-JUN-2009_1')
        )
)
 
process.SiStripConfigDb.TNS_ADMIN = '/etc'  # for P5 only!


process.SiStripCondObjBuilderFromDb = cms.Service("SiStripCondObjBuilderFromDb")
process.FedCablingFromConfigDb = cms.ESSource("SiStripFedCablingBuilderFromDb",
  CablingSource = cms.untracked.string('UNDEFINED')   ## <-- this should be replaced by "DEVICES" for a connection run!
)

# strip digitizer
process.load( "EventFilter.SiStripRawToDigi.SiStripDigis_cfi" )
process.siStripDigis.ProductLabel = "hltTrackerCalibrationRaw"

# Raw Data Converter
process.load('Alignment.LaserAlignment.RawDataConverter_cfi')
process.RawDataConverter.OutputFileName = cms.untracked.string('__OUTPUT_FILENAME_IN_ROOT_FORMAT__') #@@@ output file
process.RawDataConverter.SortOutput = cms.bool(False)

# Run the LAS analysis
process.p = cms.Path(process.siStripDigis + process.RawDataConverter)

