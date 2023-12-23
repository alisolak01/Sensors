clear all
close all

dist_meas = [0;10;20;30;40;50;60;70;80;90;100;110;120];
fratio_meas = [4301540;4305060;4310452;4318000;4326960;4336760;4348505;4361409;4374537;4387925;4401741;4416442;4435065];

inductive_sensor = serialport("COM7", 115200);
configureTerminator(inductive_sensor, "CR/LF");
flush(inductive_sensor);

global min_offset_array
global max_offset_array

min_offset_array = [0];
max_offset_array = [0];

global min_cal_offset;
global max_cal_offset;

min_cal_offset = 0;
max_cal_offset = 0;

%% Offset meas

fprintf('Place slider at 0cm.\n')
fprintf('Do not touch.\n')

input('Press ''Enter'' to continue...','s');

tStart = tic;
tEnd = toc(tStart);

flush(inductive_sensor);

while (tEnd < 5) %min error meas
    flush(inductive_sensor);
    data_line = readline(inductive_sensor);
    fratio_data = double(data_line);
    min_offset_array = [min_offset_array; fratio_data];
    tEnd = toc(tStart);
    pause(1e-3);
end

fprintf('Calibration Done.\n')

min_cal_offset = sum(min_offset_array)/(length(min_offset_array) - 1)

fprintf('Place slider at 12cm.\n')
fprintf('Do not touch.\n')

input('Press ''Enter'' to continue...','s');


tStart = tic;
tEnd = toc(tStart);

flush(inductive_sensor);

while (tEnd < 5) %max error meas
    flush(inductive_sensor);
    data_line = readline(inductive_sensor);
    fratio_data = double(data_line);
    max_offset_array = [max_offset_array; fratio_data];
    tEnd = toc(tStart);
    pause(1e-3);
end

max_cal_offset = sum(max_offset_array)/(length(max_offset_array) - 1)

%% Re-evaluate fratio_meas array

range_cal_offset = max_cal_offset - min_cal_offset
range_cal_table = max(fratio_meas) - min(fratio_meas)

fratio_meas = fratio_meas * (range_cal_offset/range_cal_table);

fratio_meas = fratio_meas - (fratio_meas(1,1) - min_cal_offset);

global calib_table
calib_table = table(dist_meas,fratio_meas);

flush(inductive_sensor);

while (1)
   flush(inductive_sensor);
   data_line = readline(inductive_sensor);
   fratio_data = double(data_line);
   dist_val = val_to_dist(fratio_data)
   pause(1e-3);
end

function [dist] = val_to_dist(val)

    % calibration
    global calib_table

    dist = interp1(calib_table.fratio_meas,calib_table.dist_meas,val);

end
