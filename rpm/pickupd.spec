Name:       pickupd

%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}

Summary:    Pickup Sensor Handler
Version:    0.0.1
Release:    1
Group:      Qt/Qt
License:    MIT
URL:        https://github.com/sailfishos-sony-tama/pickupd
Source0:    %{name}-%{version}.tar.bz2
Requires:   sensorfw-qt5 > 0.8.30
Requires:   hybris-libsensorfw-qt5 > 0.8.30

BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(sensord-qt5)
BuildRequires:  sensorfw-qt5-devel

%description
%{summary}


%prep
%setup -q -n %{name}-%{version}

%build

%qtc_qmake5 SPECVERSION=%{version}

%qtc_make %{?_smp_mflags}

%install
rm -rf %{buildroot}

%qmake5_install

%preun
# in case of complete removal, stop and disable
if [ "$1" = "0" ]; then
  systemctl-user disable %{name}
  systemctl-user stop %{name}
fi

%post
systemctl-user daemon-reload
systemctl-user start %{name}
systemctl-user enable %{name}

%pre
# In case of update, stop first
if [ "$1" = "2" ]; then
  systemctl-user disable %{name}
  systemctl-user stop %{name}
fi

%files
%defattr(644,root,root,755)
%attr(755,root,root) %{_bindir}/%{name}
%config %{_sysconfdir}/systemd/user/
