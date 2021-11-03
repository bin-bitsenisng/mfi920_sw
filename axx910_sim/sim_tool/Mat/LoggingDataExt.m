function [ DataCell ] = LoggingDataExt( Target_Folder, dsetname)
% Data Extraction

dirData = dir(Target_Folder);
DirIndex = [dirData.isdir];
DirList = {dirData(DirIndex).name}';
validIndex = ~ismember(DirList,{'.','..'});
DirList = DirList(validIndex);
DirList{end+1,1} = '';

fileCnt = 0;
DataCell = cell(length(DirList),1);
for folder_idx = 1:length(DirList)
    Log_Folder = [Target_Folder, '\', DirList{folder_idx,1}];
    [fileList, sub_Folder] = getAllFiles(Log_Folder);

    h5file = 'None';
    for ii=1:length(fileList)
        [pathstr,name,ext] = fileparts(fileList{ii});
        if strcmp(ext,'.h5')
            h5file = fileList{ii};
        end
    end

    if ~strcmp(h5file, 'None')
        fileCnt = fileCnt+1;
        num_scan = double(h5read(h5file, '/DataInfo/endScanIndex'));
        DataCell{fileCnt} = cell(num_scan,1);
        
        for m = 1:num_scan
            gname = ['/SCAN_',num2str(m,'%05d')];
            dset = double(h5read(h5file, [gname,dsetname])');
            DataCell{fileCnt}{m} = dset;
        end
    else
        DataCell(folder_idx) = [];
    end
    
end

end

