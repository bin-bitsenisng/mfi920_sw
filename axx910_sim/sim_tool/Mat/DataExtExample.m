close all;
clear vars;
clc;



%% Data Information
Target_Folder = 'C:\RADAR\0.Resim_Code\GIT\MRR30_SP\Simulation\CanLoggingData\180222_PGTest\Coverage';
dsetname = '/Sim_ObjInfo';

%%
DataCell = LoggingDataExt(Target_Folder, dsetname);

for ii = 1:length(DataCell)
    for jj = 1:length(DataCell{ii})
        aa = DataCell{ii}{jj};
    end
end







