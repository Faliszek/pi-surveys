open TW;
open Belt;

let formatDate = s => {
  let date = s->Js.Date.fromString->Js.Date.toLocaleDateString;
  let time = s->Js.Date.fromString->Js.Date.toLocaleTimeString;

  date ++ ", " ++ time;
};

let th = () =>
  [
    TextAlign(TextLeft),
    Padding(P2),
    Padding(Px6),
    BorderStyle(BorderSolid),
    BorderWidth(BorderB),
    BorderColor(BorderGray400),
  ]
  ->make;

let td = w =>
  [
    TextAlign(TextLeft),
    Padding(Py6),
    Padding(Px6),
    BorderStyle(BorderSolid),
    BorderWidth(BorderB),
    BorderColor(BorderGray200),
    Width(w),
  ]
  ->make;

[@react.component]
let make = () => {
  let (page, setPage) = React.useState(_ => 1);

  let (surveyId, setSurveyId) = React.useState(() => "");
  let (name, setName) = React.useState(() => "");
  let (email, setEmail) = React.useState(() => "");
  let (number, setNumber) = React.useState(() => "");

  let (surveys, executeQuery) = ResultsQuery.use(~page, ());

  <Layout>
    <div className={[Display(Flex), JustifyContent(JustifyBetween)]->make}>
      <Text className=TW.[FontSize(Text2xl), Margin(Mr4)]>
        {j|Wyniki|j}
      </Text>
    </div>
    <div className={[Display(Flex), Margin(My8)]->make}>
      <Input
        value=surveyId
        onChange={v => setSurveyId(_ => v)}
        placeholder={j|ID Ankiety|j}
        className=[Margin(Mr8)]
      />
      <Input
        value=name
        onChange={v => setName(_ => v)}
        placeholder={j|Imię i nazwisko|j}
        className=[Margin(Mr8)]
      />
      <Input
        value=number
        onChange={v => setNumber(_ => v)}
        placeholder={j|Numer albumu|j}
        className=[Margin(Mr8)]
      />
      <Input
        value=email
        onChange={v => setEmail(_ => v)}
        placeholder={j|E-mail|j}
        className=[Margin(Mr8)]
      />
      <Button onClick={_ => executeQuery(~context="") |> ignore}>
        <Text> {j|Szukaj|j} </Text>
      </Button>
    </div>
    {switch (surveys.response) {
     | Data(data) =>
       //mocks
       let solutions =
         data##solutions
         ->Option.map(e => e##entries)
         ->Option.getWithDefault([||])
         ->Array.map(f =>
             {
               "_id": f##_id,
               "name": f##name,
               "number": f##number,
               "email": f##email,
             }
           );

       let total =
         data##solutions->Option.map(s => s##total)->Option.getWithDefault(0);

       switch (total) {
       | 0 => <Text> {j|Brak wyników|j} </Text>
       | _ =>
         <div>
           <table
             className={
               [
                 Width(WFull),
                 Margin(My8),
                 BorderRadius(RoundedLg),
                 BoxShadow(Shadow),
                 Padding(P8),
               ]
               ->make
             }>
             <thead>
               <tr>
                 <th className={th()}> <Text> {j|ID|j} </Text> </th>
                 <th className={th()}> <Text> {j|Uczestnik|j} </Text> </th>
                 <th className={th()}> <Text> {j|Numer albumu|j} </Text> </th>
                 <th className={th()}> <Text> {j|Email|j} </Text> </th>
               </tr>
             </thead>
             <tbody>
               {solutions
                ->Belt.Array.map(s =>
                    <tr key={s##_id}>
                      <td className={td(W1_6)}> <Text> {s##_id} </Text> </td>
                      <td className={td(W1_6)}> <Text> {s##name} </Text> </td>
                      <td className={td(W1_6)}>
                        <Text> {s##number} </Text>
                      </td>
                      <td className={td(W3_12)}>
                        <Text> {s##email} </Text>
                      </td>
                    </tr>
                  )
                ->React.array}
             </tbody>
           </table>
           <div
             className={[Display(Flex), JustifyContent(JustifyEnd)]->make}>
             {Array.range(1, total)
              ->Array.map(v =>
                  <div
                    key={v->Js.Int.toString}
                    className={
                      [
                        Width(W12),
                        Height(H12),
                        BoxShadow(ShadowMd),
                        BorderRadius(RoundedLg),
                        Display(Flex),
                        AlignItems(ItemsCenter),
                        JustifyContent(JustifyCenter),
                        Margin(M1),
                        BackgroundColor(BgGray100),
                        Cursor(CursorPointer),
                      ]
                      ->make
                    }
                    onClick={_ => setPage(_ => v)}>
                    <Text> v->Js.Int.toString </Text>
                  </div>
                )
              ->React.array}
           </div>
         </div>
       };
     | Fetching => <Text> {j|Wczytywanie|j} </Text>
     | NotFound => React.null
     | Error(_) => <Text> {j|Wystąpił nieoczekiwany błąd|j} </Text>
     }}
  </Layout>;
};